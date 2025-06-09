/**
 * @file syspanel.hpp
 * @author Dessera (dessera@qq.com)
 * @brief System information panel.
 * @version 0.1.0
 * @date 2025-06-09
 *
 * @copyright Copyright (c) 2025 Dessera
 *
 */

#pragma once

#include <qwidget.h>

namespace tde::widgets::startmenu {

/**
 * @brief System information panel.
 *
 */
class SysPanel : public QWidget
{
  Q_OBJECT

public:
  /**
   * @brief Construct a new Sys Panel object.
   *
   * @param parent Parent widget.
   */
  SysPanel(QWidget* parent = nullptr);
  ~SysPanel() override = default;
};

}
