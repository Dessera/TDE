/**
 * @file fetcher.hpp
 * @author Dessera (dessera@qq.com)
 * @brief Application fetcher from local config file.
 * @version 0.1.0
 * @date 2025-06-12
 *
 * @copyright Copyright (c) 2025 Dessera
 *
 */

#pragma once

#include <qfile.h>
#include <qfilesystemwatcher.h>
#include <qobject.h>

#include "tde/app/info.hpp"
#include "tde/common.hpp"
#include "tde/settings.hpp"

namespace tde::app {

/**
 * @brief Application fetcher from local config file.
 *
 */
class TDE_EXPORT Fetcher : public QObject
{
  Q_OBJECT

private:
  QFileSystemWatcher* _watcher;
  QString _target_path;

public:
  /**
   * @brief Construct a new Fetcher object.
   *
   * @param settings Desktop settings.
   * @param parent Parent object.
   */
  Fetcher(const DesktopSettings& settings, QObject* parent = nullptr);
  ~Fetcher() override = default;

  /**
   * @brief Refresh the application list.
   *
   */
  void refresh();

private:
  /**
   * @brief Remount the file watcher, used in linux due to the BUG of
   * QFileSystemWatcher.
   *
   * @param file File to watch.
   * @param path Path of the file.
   */
  void _remount_watcher(const QFile& file, const QString& path);

signals:
  /**
   * @brief Emitted when the application list changed.
   *
   * @param apps List of application info.
   */
  void apps_changed(const QList<Info>& apps);

  /**
   * @brief Emitted when the dock app list changed.
   *
   * @param apps List of dock app info.
   */
  void dock_apps_changed(const QList<Info>& apps);

private slots:
  /**
   * @brief Handle the file changed event.
   *
   * @param path Path of the file.
   */
  void _on_file_changed(const QString& path);
};

}
