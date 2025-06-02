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

#include "tde/helpers/appfetcher.hpp"

namespace {

constexpr bool
_json_is_appinfo(const QJsonValue& value)
{
  if (!value.isObject()) {
    return false;
  }

  auto obj = value.toObject();

  if (!obj.contains("Name") || !obj.contains("Icon") || !obj.contains("Exec")) {
    return false;
  }

  if (!obj.value("Name").isString() || !obj.value("Icon").isString() ||
      !obj.value("Exec").isString()) {
    return false;
  }

  return true;
}

constexpr tde::helpers::AppInfo
_json_to_appinfo(const QJsonValue& value)
{
  auto obj = value.toObject();
  return tde::helpers::AppInfo{ .name = obj["Name"].toString(),
                                .exec = obj["Exec"].toString(),
                                .icon = obj["Icon"].toString() };
}

}

namespace tde::helpers {

AppFetcher::AppFetcher(const AppSettings& settings, QObject* parent)
  : QObject{ parent }
  , _watcher{ new QFileSystemWatcher{ this } }
  , _target_path{ settings.desktop_app_path() }
{
  _init(settings);
}

void
AppFetcher::_init(const AppSettings& /*settings*/)
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

  if (!file.open(QFile::ReadOnly)) {
    qWarning() << "Cannot open file" << path << file.errorString();
    _remount_watcher(file, path);
    return;
  }

  QJsonParseError err;
  auto json_doc = QJsonDocument::fromJson(file.readAll(), &err);
  if (err.error != QJsonParseError::NoError) {
    qWarning() << "Cannot parse json:" << err.errorString();
    _remount_watcher(file, path);
    return;
  }

  if (!json_doc.isArray()) {
    qWarning() << "Apps json is not an array:" << path;
    _remount_watcher(file, path);
    return;
  }

  auto apps = json_doc.array() | views::filter(_json_is_appinfo) |
              views::transform(_json_to_appinfo) | ranges::to<QList<AppInfo>>();

  emit apps_changed(apps);

  _remount_watcher(file, path);
}

}
