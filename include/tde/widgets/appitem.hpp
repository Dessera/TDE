/**
 * @file appitem.hpp
 * @author Dessera (dessera@qq.com)
 * @brief Application item widget.
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

namespace tde::widgets {

/**
 * @brief Application item widget.
 *
 */
class TDE_EXPORT AppItem : public QToolButton
{
  Q_OBJECT

public:
  constexpr static int IconSize =
    48; /**< Default icon size, which is immutable now. */

private:
  QString _exec;

public:
  /**
   * @brief Construct a new App Item object.
   *
   * @param app App info.
   * @param parent Parent widget.
   */
  AppItem(const app::Info& app, QWidget* parent = nullptr);
  ~AppItem() override = default;

  /**
   * @brief Get the exec command.
   *
   * @return QString Exec command.
   */
  [[nodiscard]] constexpr auto& exec() const { return _exec; }

  /**
   * @brief Convert the app item to app info.
   *
   * @return app::Info App info.
   */
  [[nodiscard]] app::Info to_app_info() const;

signals:
  /**
   * @brief Emitted when the app is requested to be launched.
   *
   * @param app App info.
   */
  void request_launch_app(const app::Info& app);

private slots:
  /**
   * @brief Emits request_launch_app signal when the button is released.
   *
   */
  void _on_released();
};

}
