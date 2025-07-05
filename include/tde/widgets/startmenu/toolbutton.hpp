/**
 * @file toolbutton.hpp
 * @author Dessera (dessera@qq.com)
 * @brief Tool button in start menu.
 * @version 0.1.0
 * @date 2025-06-09
 *
 * @copyright Copyright (c) 2025 Dessera
 *
 */

#pragma once

#include <qtoolbutton.h>

#include "tde/common.hpp"
#include "tde/startmenu.hpp"

namespace tde::widgets::startmenu {

using namespace tde::startmenu;

/**
 * @brief Tool button in start menu.
 *
 */
class TDE_PUBLIC ToolButton : public QToolButton
{
  Q_OBJECT

public:
  constexpr static int ICON_SIZE = 48; /**< Icon size. */

  /**
   * @brief Construct a new Tool Button object.
   *
   * @param info Tool info.
   * @param parent Parent widget.
   */
  ToolButton(const ToolInfo& info, QWidget* parent = nullptr);
  ~ToolButton() override = default;
};

}
