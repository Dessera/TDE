/**
 * @file startmenubutton.hpp
 * @author Dessera (dessera@qq.com)
 * @brief Start menu icon button.
 * @version 0.1.0
 * @date 2025-06-09
 *
 * @copyright Copyright (c) 2025 Dessera
 *
 */

#pragma once

#include <qtoolbutton.h>

namespace tde::widgets::tray {

/**
 * @brief Start menu button.
 *
 */
class StartMenuButton : public QToolButton
{
  Q_OBJECT

public:
  constexpr static const char* StartMenuIcon =
    ":/assets/icons/start-menu.svg";           /**< Path of start menu icon. */
  constexpr static int StartMenuIconSize = 24; /**< Size of start menu icon. */

  /**
   * @brief Construct a new Start Menu Button object.
   *
   * @param parent Parent widget.
   */
  explicit StartMenuButton(QWidget* parent = nullptr);
  ~StartMenuButton() override = default;
};

}
