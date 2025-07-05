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

#include "tde/common.hpp"
#include "tde/widgets/startmenu.hpp"

namespace tde::widgets::tray {

/**
 * @brief Start menu button.
 *
 */
class TDE_PUBLIC StartMenuButton : public QToolButton
{
  Q_OBJECT

private:
  StartMenu* _start_menu;

public:
  constexpr static const char* START_MENU_ICON =
    ":/assets/icons/start-menu.svg"; /**< Path of start menu icon. */
  constexpr static int START_MENU_ICON_SIZE =
    24; /**< Size of start menu icon. */

  /**
   * @brief Construct a new Start Menu Button object.
   *
   * @param parent Parent widget.
   */
  explicit StartMenuButton(QWidget* parent = nullptr);
  ~StartMenuButton() override = default;

private slots:
  /**
   * @brief Handle the released event.
   *
   */
  void _on_released();
};

}
