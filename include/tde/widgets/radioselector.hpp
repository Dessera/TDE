/**
 * @file radioselector.hpp
 * @author Dessera (dessera@qq.com)
 * @brief AppListCard selector
 * @version 0.1.0
 * @date 2025-06-03
 *
 * @copyright Copyright (c) 2025 Dessera
 *
 */

#pragma once

#include <qradiobutton.h>
#include <qtmetamacros.h>
#include <qwidget.h>

namespace tde::widgets {

/**
 * @brief Group of radio buttons used for selecting an item.
 *
 */
class RadioSelector : public QWidget
{
  Q_OBJECT

private:
  QList<QRadioButton*> _buttons;

public:
  /**
   * @brief Construct a new Radio Selector object.
   *
   * @param parent Parent widget.
   */
  RadioSelector(QWidget* parent = nullptr);
  ~RadioSelector() override = default;

  /**
   * @brief Set the count of radio buttons.
   *
   * @param count Number of radio buttons.
   */
  void set_count(int count);

  /**
   * @brief Set the selected index (do not trig the signal).
   *
   * @param index Index of the selected button.
   */
  void set_current(int index);

private:
  /**
   * @brief Create a new radio button.
   *
   */
  void _create_button();

  /**
   * @brief Clear all radio buttons.
   *
   */
  void _clear_buttons();

signals:
  /**
   * @brief Emitted when a radio button is selected.
   *
   * @param index Index of the selected button.
   */
  void selected(int index);

private slots:
  /**
   * @brief Emit the selected signal when a radio button is released.
   *
   */
  void on_button_released();
};

}
