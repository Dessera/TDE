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

#include "tde/common.hpp"
#include "tde/startmenu.hpp"

namespace tde::widgets::startmenu {

using namespace tde::startmenu;

/**
 * @brief Tool buttons in start menu.
 *
 */
class TDE_PUBLIC ToolPanel : public QWidget
{
  Q_OBJECT

public:
  inline static const QList<ToolInfo> Tools = {
    { "Logout", "echo Logout", ":/assets/icons/logout.svg" },
    {
      "Reboot",
      "echo reboot",
      ":/assets/icons/reboot.svg",
    },
    {
      "Shutdown",
      "echo shutdown",
      ":/assets/icons/shutdown.svg",
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
