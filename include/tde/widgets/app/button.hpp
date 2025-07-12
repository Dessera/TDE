/**
 * @file button.hpp
 * @author Dessera (dessera@qq.com)
 * @brief Application launcher button.
 * @version 0.1.0
 * @date 2025-06-02
 *
 * @copyright Copyright (c) 2025 Dessera
 *
 */

#pragma once

#include <qtoolbutton.h>

#include "tde/app/info.hpp"
#include "tde/common.hpp"

namespace tde::widgets::app {

/**
 * @brief Application launcher button.
 *
 */
class TDE_PUBLIC Button : public QToolButton
{
  Q_OBJECT

public:
  using AppInfo = tde::app::Info;

private:
  QString _exec;

public:
  /**
   * @brief Construct a new App Button object.
   *
   * @param app App info.
   * @param parent Parent widget.
   */
  Button(const AppInfo& app, QWidget* parent = nullptr);

  ~Button() override = default;

  /**
   * @brief Get the exec command.
   *
   * @return QString Exec command.
   */
  [[nodiscard]] TDE_INLINE auto& exec() const { return _exec; }

  /**
   * @brief Convert the app item to app info.
   *
   * @return AppInfo App info.
   */
  [[nodiscard]] AppInfo to_app_info() const;

signals:
  /**
   * @brief Emitted when the app is requested to be launched.
   *
   * @param app App info.
   */
  void request_launch_app(const AppInfo& app);

private slots:
  /**
   * @brief Emits request_launch_app signal when the button is released.
   *
   */
  void _on_clicked();
};

}
