/**
 * @file applauncher.hpp
 * @author Dessera (dessera@qq.com)
 * @brief Application launcher
 * @version 0.1.0
 * @date 2025-06-02
 *
 * @copyright Copyright (c) 2025 Dessera
 *
 */

#pragma once

#include <qobject.h>
#include <qprocess.h>
#include <qtmetamacros.h>

#include "tde/helpers/appfetcher.hpp"
#include "tde/settings.hpp"

namespace tde::helpers {

/**
 * @brief Application launcher
 *
 */
class AppLauncher : public QObject
{
  Q_OBJECT

public:
  /**
   * @brief Construct a new App Launcher object.
   *
   * @param settings Desktop settings.
   * @param parent Parent object.
   */
  AppLauncher(const DesktopSettings& settings, QObject* parent = nullptr);
  ~AppLauncher() override = default;

signals:
  /**
   * @brief Emitted before app is launched.
   *
   * @param app Application information.
   */
  void start_app(const helpers::AppInfo& app);

  /**
   * @brief Emitted after app is launched.
   *
   * @param code Exit code.
   * @param status Exit status.
   */
  void finish_app(int code, QProcess::ExitStatus status);

public slots: // NOLINT
  /**
   * @brief Launch an application.
   *
   * @param app Application information.
   */
  void on_request_launch_app(const helpers::AppInfo& app);

private slots:
  /**
   * @brief Hook after app is finished, for cleanup.
   *
   * @param code Exit code.
   * @param status Exit status.
   */
  void on_finish_app(int code, QProcess::ExitStatus status);
};

}
