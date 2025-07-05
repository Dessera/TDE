/**
 * @file clock.hpp
 * @author Dessera (dessera@qq.com)
 * @brief Clock label for tray.
 * @version 0.1.0
 * @date 2025-06-09
 *
 * @copyright Copyright (c) 2025 Dessera
 *
 */

#pragma once

#include <qlabel.h>

#include "tde/common.hpp"

namespace tde::widgets::tray {

/**
 * @brief Clock label for tray.
 *
 */
class TDE_PUBLIC Clock : public QLabel
{
  Q_OBJECT

public:
  constexpr static int TIME_UPDATE_INTERVAL =
    1000; /**< Time update interval. */

private:
  QString _format;
  QTimer* _timer;

public:
  /**
   * @brief Construct a new Clock object.
   *
   * @param format Time format.
   * @param parent Parent widget.
   */
  Clock(QString format, QWidget* parent = nullptr);
  ~Clock() override = default;

private slots:
  /**
   * @brief Emitted when the timer times out.
   *
   */
  void _on_timeout();
};

}
