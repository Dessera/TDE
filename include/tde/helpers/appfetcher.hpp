#pragma once

#include <qfile.h>
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
  QString _target_path;

public:
  AppFetcher(const AppSettings& settings, QObject* parent = nullptr);
  ~AppFetcher() override = default;

  /**
   * @brief Manually refresh the list of apps (trigger the fileChanged signal)
   *
   */
  void refresh();

private:
  /**
   * @brief Initializes sinals and slots
   *
   * @param settings The settings of the app
   */
  void _init(const AppSettings& settings);

  /**
   * @brief Remounts the watcher to the given file and path
   *
   * @param file The file to watch
   * @param path The path of the file
   *
   * @note Due to the BUG in QFileSystemWatcher, we need to remount the watcher
   * after fileChanged signal
   */
  void _remount_watcher(const QFile& file, const QString& path);

signals:
  /**
   * @brief Emitted when the list of apps changed
   *
   * @param apps The new list of apps
   */
  void apps_changed(const QList<AppInfo>& apps);

private slots:
  /**
   * @brief Emits the apps_changed signal with the new list of apps
   *
   * @param path The path of the file that changed
   */
  void _on_file_changed(const QString& path);
};

}
