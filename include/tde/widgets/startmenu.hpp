/**
 * @file startmenu.hpp
 * @author Dessera (dessera@qq.com)
 * @brief Start menu widget.
 * @version 0.1.0
 * @date 2025-06-09
 *
 * @copyright Copyright (c) 2025 Dessera
 *
 */

#pragma once

#include <qwidget.h>

#include "tde/common.hpp"

namespace tde::widgets {

/**
 * @brief Start menu widget.
 *
 */
class TDE_EXPORT StartMenu : public QWidget
{
  Q_OBJECT

public:
  /**
   * @brief Construct a new Start Menu object.
   *
   * @param parent Parent widget.
   */
  StartMenu(QWidget* parent = nullptr);
  ~StartMenu() override = default;

protected:
  /**
   * @brief Handle show event.
   *
   * @param event Show event.
   */
  void showEvent(QShowEvent* event) override;

  /**
   * @brief Handle mouse press event.
   *
   * @param event Mouse press event.
   */
  void mousePressEvent(QMouseEvent* event) override;

  /**
   * @brief Handle key press event.
   *
   * @param event Key press event.
   */
  void keyPressEvent(QKeyEvent* event) override;

private:
  /**
   * @brief Initialize the widget.
   *
   */
  void _init();

  /**
   * @brief Initialize the UI components.
   *
   */
  void _init_ui();
};

}
