#include <qfile.h>
#include <qfilesystemwatcher.h>
#include <qjsonarray.h>
#include <qjsondocument.h>
#include <qjsonobject.h>
#include <qjsonparseerror.h>
#include <qjsonvalue.h>
#include <qlist.h>
#include <qlogging.h>
#include <qobjectdefs.h>
#include <ranges>

#include "tde/common.hpp"
#include "tde/helpers/appfetcher.hpp"

namespace {

constexpr bool
_json_is_apps(const QJsonDocument& doc)
{
  if (!doc.isObject()) {
    return false;
  }

  auto obj = doc.object();

  return obj.contains("apps") && obj.value("apps").isArray() &&
         obj.contains("dock_apps") && obj.value("dock_apps").isArray();
}

constexpr bool
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

constexpr tde::helpers::AppInfo
_json_to_appinfo(const QJsonValue& value)
{
  auto obj = value.toObject();
  return tde::helpers::AppInfo{ .name = obj["name"].toString(),
                                .exec = obj["exec"].toString(),
                                .icon = obj["icon"].toString() };
}

}

namespace tde::helpers {

AppFetcher::AppFetcher(const DesktopSettings& settings, QObject* parent)
  : QObject{ parent }
  , _watcher{ new QFileSystemWatcher{ this } }
  , _target_path{ settings.desktop_app_path() }
{
  _init(settings);
}

void
AppFetcher::_init(const DesktopSettings& /*settings*/)
{
  _watcher->addPath(_target_path);

  connect(_watcher,
          &QFileSystemWatcher::fileChanged,
          this,
          &AppFetcher::_on_file_changed);

  qInfo() << "Fetching app items from:" << _target_path;
}

void
AppFetcher::_remount_watcher(const QFile& file, const QString& path)
{
  if (file.exists() || !_watcher->files().contains(path)) {
    _watcher->addPath(path);
  }
}

void
AppFetcher::refresh()
{
  QMetaObject::invokeMethod(_watcher, "fileChanged", _target_path);
}

void
AppFetcher::_on_file_changed(const QString& path)
{
  namespace ranges = std::ranges;
  namespace views = std::ranges::views;

  auto file = QFile{ path };
  tde_defer(_remount_watcher(file, path));

  if (!file.open(QFile::ReadOnly)) {
    qWarning() << "Cannot open file:" << path << file.errorString();
    return;
  }

  QJsonParseError err;
  auto json_doc = QJsonDocument::fromJson(file.readAll(), &err);
  if (err.error != QJsonParseError::NoError) {
    qWarning() << "Cannot parse json:" << err.errorString();
    return;
  }

  if (!_json_is_apps(json_doc)) {
    qWarning() << "Apps json format error";
    return;
  }

  auto json_apps = json_doc.object().value("apps").toArray();
  auto apps = json_apps | views::filter(_json_is_appinfo) |
              views::transform(_json_to_appinfo) | ranges::to<QList<AppInfo>>();

  qInfo() << "Reloaded" << apps.size() << "apps from:" << path;

  emit apps_changed(apps);

  auto json_dock_apps = json_doc.object().value("dock_apps").toArray();
  auto dock_apps = json_dock_apps | views::filter(_json_is_appinfo) |
                   views::transform(_json_to_appinfo) |
                   ranges::to<QList<AppInfo>>();

  qInfo() << "Reloaded" << dock_apps.size() << "dock apps from:" << path;

  emit dock_apps_changed(dock_apps);
}

}
