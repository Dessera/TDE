#include <qjsonarray.h>
#include <qjsondocument.h>
#include <qjsonobject.h>
#include <qjsonparseerror.h>
#include <qjsonvalue.h>
#include <qlist.h>
#include <qlogging.h>

#include "tde/app/fetcher.hpp"
#include "tde/common.hpp"

namespace {

bool
_json_is_apps(const QJsonDocument& doc)
{
  if (!doc.isObject()) {
    return false;
  }

  auto obj = doc.object();

  return obj.contains("apps") && obj.value("apps").isArray() &&
         obj.contains("dock_apps") && obj.value("dock_apps").isArray();
}

bool
_json_is_appinfo(const QJsonValue& value)
{
  if (!value.isObject()) {
    return false;
  }

  auto obj = value.toObject();

  if (!obj.contains("name") || !obj.contains("exec") || !obj.contains("icon")) {
    return false;
  }

  if (!obj.value("name").isString() || !obj.value("exec").isString() ||
      !obj.value("icon").isString()) {
    return false;
  }

  return true;
}

TDE_INLINE tde::app::Info
_json_to_appinfo(const QJsonValue& value)
{
  auto obj = value.toObject();
  return { obj["name"].toString(),
           obj["exec"].toString(),
           obj["icon"].toString() };
}

QList<tde::app::Info>
_json_to_appinfo_list(const QJsonArray& array)
{
  auto res = QList<tde::app::Info>{};

  for (const auto& value : array) {
    if (_json_is_appinfo(value)) {
      res.append(_json_to_appinfo(value));
    }
  }

  return res;
}

}

namespace tde::app {

Fetcher::Fetcher(QString target_path, QObject* parent)
  : QObject{ parent }
  , _watcher{ new QFileSystemWatcher{ this } }
  , _target_path{ std::move(target_path) }
{
  _watcher->addPath(_target_path);

  connect(_watcher,
          &QFileSystemWatcher::fileChanged,
          this,
          &Fetcher::_on_file_changed);

  qInfo() << "Fetching app items from:" << _target_path;
}

void
Fetcher::_remount_watcher(const QFile& file, const QString& path)
{
  if (file.exists() || !_watcher->files().contains(path)) {
    _watcher->addPath(path);
  }
}

void
Fetcher::refresh()
{
  QMetaObject::invokeMethod(_watcher, "fileChanged", _target_path);
}

void
Fetcher::_on_file_changed(const QString& path)
{
  auto file = QFile{ path };
  tde_defer(_remount_watcher(file, path));

  if (!file.open(QFile::ReadOnly)) {
    qWarning() << "Failed to open dekstop apps file:" << file.errorString();
    return;
  }

  QJsonParseError err;
  auto json_doc = QJsonDocument::fromJson(file.readAll(), &err);
  if (err.error != QJsonParseError::NoError) {
    qWarning() << "Failed to parse desktop apps file:" << err.errorString();
    return;
  }

  if (!_json_is_apps(json_doc)) {
    qWarning() << "Failed to parse desktop apps file: Apps json format error";
    return;
  }

  auto apps = _json_to_appinfo_list(json_doc.object().value("apps").toArray());

  qInfo() << "Reloaded" << apps.size() << "apps from:" << path;
  emit apps_changed(apps);

  auto dock_apps =
    _json_to_appinfo_list(json_doc.object().value("dock_apps").toArray());

  qInfo() << "Reloaded" << dock_apps.size() << "dock apps from:" << path;
  emit dock_apps_changed(dock_apps);
}

}
