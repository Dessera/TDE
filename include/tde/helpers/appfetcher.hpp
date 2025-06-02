/**
 * @file appfetcher.hpp
 * @author Dessera (dessera@qq.com)
 * @brief Wrapper for QFileSystemWatcher to fetch the list of apps
 * @version 0.1.0
 * @date 2025-06-02
 *
 * @copyright Copyright (c) 2025 Dessera
 *
 */

#pragma once

#include <qfile.h>
#include <qfilesystemwatcher.h>
#include <qobject.h>
#include <qtmetamacros.h>

#include "tde/settings.hpp"

namespace tde::helpers {

/**
 * @brief Application info struct.
 *
 */
struct AppInfo
{
  QString name;
  QString exec;
  QString icon;
};

/**
 * @brief Fetches the list of apps from the given path (in the settings).
 *
 */
class AppFetcher : public QObject
{
  Q_OBJECT

private:
  QFileSystemWatcher* _watcher;
  QString _target_path;

public:
  /**
   * @brief Construct a new App Fetcher object.
   *
   * @param settings Desktop settings.
   * @param parent Parent object.
   */
  AppFetcher(const DesktopSettings& settings, QObject* parent = nullptr);
  ~AppFetcher() override = default;

  /**
   * @brief Manually refresh the list of apps (trigger the fileChanged signal).
   *
   */
  void refresh();

private:
  /**
   * @brief Initializes sinals and slots.
   *
   * @param settings Desktop settings.
   */
  void _init(const DesktopSettings& settings);

  /**
   * @brief Remounts the watcher to the given file and path.
   *
   * @param file File to watch.
   * @param path Path of the file.
   *
   * @note Due to the BUG in QFileSystemWatcher, we need to remount the watcher
   * after fileChanged signal.
   */
  void _remount_watcher(const QFile& file, const QString& path);

signals:
  /**
   * @brief Emitted when the list of apps changed.
   *
   * @param apps New list of apps.
   */
  void apps_changed(const QList<AppInfo>& apps);

private slots:
  /**
   * @brief Emits the apps_changed signal with the new list of apps.
   *
   * @param path Path of the file that changed.
   */
  void _on_file_changed(const QString& path);
};

}
