/**
 * @file monitor.hpp
 * @author Dessera (dessera@qq.com)
 * @brief Monitor widgets.
 * @version 0.1.0
 * @date 2025-07-15
 *
 * @copyright Copyright (c) 2025 Dessera
 *
 */

#pragma once

#include <qwidget.h>
#include <tde/settings.hpp>

/**
 * @brief Monitor main widget.
 *
 */
class Monitor : public QWidget
{
  Q_OBJECT

public:
  /**
   * @brief Construct a new Monitor object.
   *
   * @param settings Desktop settings.
   * @param parent Parent widget.
   */
  Monitor(const tde::DesktopSettings& settings, QWidget* parent = nullptr);

  ~Monitor() override = default;
};
