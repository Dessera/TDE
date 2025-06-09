/**
 * @file toolpanel.hpp
 * @author Dessera (dessera@qq.com)
 * @brief Tool buttons in start menu.
 * @version 0.1.0
 * @date 2025-06-09
 *
 * @copyright Copyright (c) 2025 Dessera
 *
 */

#pragma once

#include <qwidget.h>

#include "tde/startmenu.hpp"

namespace tde::widgets::startmenu {

using namespace tde::startmenu;

/**
 * @brief Tool buttons in start menu.
 *
 */
class ToolPanel : public QWidget
{
  Q_OBJECT

public:
  inline static const QList<ToolInfo> Tools = {
    { .name = "Logout",
      .exec = "echo Logout",
      .icon = ":/assets/icons/logout.svg" },
    {
      .name = "Reboot",
      .exec = "echo reboot",
      .icon = ":/assets/icons/reboot.svg",
    },
    {
      .name = "Shutdown",
      .exec = "echo shutdown",
      .icon = ":/assets/icons/shutdown.svg",
    }
  }; /**< Buttons in panel */

  /**
   * @brief Construct a new Tool Panel object.
   *
   * @param parent Parent widget.
   */
  ToolPanel(QWidget* parent = nullptr);
  ~ToolPanel() override = default;
};

}
