#pragma once

#include <qfilesystemwatcher.h>
#include <qobject.h>
#include <qtmetamacros.h>

#include "tde/settings.hpp"

namespace tde::helpers {

struct AppInfo
{
  QString name;
  QString exec;
  QString icon;
};

class AppFetcher : public QObject
{
  Q_OBJECT

private:
  QFileSystemWatcher* _watcher;
  QString _target_dir;

public:
  AppFetcher(const AppSettings& settings, QObject* parent = nullptr);
  ~AppFetcher() override = default;

  void refresh();

private:
  void _init(const AppSettings& settings);

signals:
  void apps_changed(const QList<AppInfo>& items);

private slots:
  void _on_directory_changed(const QString& dir);
};

}
