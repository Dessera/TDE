/**
 * @file launcher.hpp
 * @author Dessera (dessera@qq.com)
 * @brief Application launcher.
 * @version 0.1.0
 * @date 2025-06-12
 *
 * @copyright Copyright (c) 2025 Dessera
 *
 */

#pragma once

#include <qobject.h>
#include <qprocess.h>

#include "tde/app/info.hpp"
#include "tde/common.hpp"

namespace tde::app {

/**
 * @brief Application launcher.
 *
 */
class TDE_PUBLIC Launcher : public QObject
{
  Q_OBJECT

public:
  /**
   * @brief Construct a new Launcher object.
   *
   * @param parent Parent object.
   */
  explicit Launcher(QObject* parent = nullptr)
    : QObject{ parent }
  {
  }

  ~Launcher() override = default;

  /**
   * @brief Launch the application.
   *
   * @param app Application info.
   */
  void launch(const Info& app);

signals:
  /**
   * @brief Emitted before the application is launched.
   *
   * @param app Application info.
   */
  void before_app_start(const Info& app);

  /**
   * @brief Emitted after the application is finished.
   *
   * @param code Exit code.
   * @param status Exit status.
   */
  void after_app_finish(int code, QProcess::ExitStatus status);

public slots:
  /**
   * @brief Launch the application.
   *
   * @param app Application info.
   */
  void on_request_launch_app(const Info& app);

private slots:
  /**
   * @brief Handle the application finished signal.
   *
   * @param code Exit code.
   * @param status Exit status.
   */
  void _on_app_finish(int code, QProcess::ExitStatus status);
};

}
