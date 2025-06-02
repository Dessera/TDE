#include <qdir.h>
#include <qfilesystemwatcher.h>
#include <qjsondocument.h>
#include <qjsonobject.h>
#include <qlogging.h>
#include <ranges>

#include "qobjectdefs.h"
#include "tde/helpers/appfetcher.hpp"

namespace {

constexpr QJsonDocument
_path_to_json(const QString& path)
{
  QFile file{ path };
  if (!file.open(QFile::ReadOnly)) {
    qWarning() << "Cannot open file:" << path;
    return {};
  }
  return QJsonDocument::fromJson(file.readAll());
}

constexpr bool
_json_is_appinfo(const QJsonDocument& doc)
{
  if (!doc.isObject()) {
    return false;
  }

  auto obj = doc.object();

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
_json_to_appinfo(const QJsonDocument& doc)
{
  auto obj = doc.object();
  return tde::helpers::AppInfo{ .name = obj["Name"].toString(),
                                .exec = obj["Exec"].toString(),
                                .icon = obj["Icon"].toString() };
}

}

namespace tde::helpers {

AppFetcher::AppFetcher(const AppSettings& settings, QObject* parent)
  : QObject{ parent }
  , _watcher{ new QFileSystemWatcher{ this } }
  , _target_dir{ settings.desktop_app_dir() }
{
  _init(settings);
}

void
AppFetcher::_init(const AppSettings& /*settings*/)
{
  auto app_dir = QDir{ _target_dir };
  if (!app_dir.exists()) {
    qWarning() << "Invalid desktop app path, cannot fetch app items:"
               << app_dir.path();
    return;
  }

  qInfo() << "Fetching app items from:" << app_dir.path();

  connect(_watcher,
          &QFileSystemWatcher::directoryChanged,
          this,
          &AppFetcher::_on_directory_changed);

  _watcher->addPath(app_dir.path());
}

void
AppFetcher::refresh()
{
  QMetaObject::invokeMethod(_watcher, "directoryChanged", _target_dir);
}

void
AppFetcher::_on_directory_changed(const QString& dir)
{
  namespace ranges = std::ranges;
  namespace views = std::ranges::views;

  auto app_dir = QDir{ dir };
  auto entries =
    app_dir.entryList(QDir::Files | QDir::NoDotAndDotDot) |
    views::filter([](const QString& file) { return file.endsWith(".te"); }) |
    views::transform(
      [&app_dir](const QString& file) { return app_dir.filePath(file); }) |
    views::transform(_path_to_json) | views::filter(_json_is_appinfo) |
    views::transform(_json_to_appinfo) | ranges::to<QList<AppInfo>>();

  emit apps_changed(entries);
}

}
