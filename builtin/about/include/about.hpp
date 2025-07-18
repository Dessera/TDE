/**
 * @file about.hpp
 * @author Dessera (dessera@qq.com)
 * @brief About widgets.
 * @version 0.1.0
 * @date 2025-07-07
 *
 * @copyright Copyright (c) 2025 Dessera
 *
 */

#pragma once

#include <qwidget.h>
#include <tde/settings.hpp>

/**
 * @brief About main widget.
 *
 */
class About : public QWidget
{
  Q_OBJECT

public:
  /**
   * @brief Construct a new About Widget object.
   *
   * @param parent Parent widget.
   */
  About(const tde::DesktopSettings& settings, QWidget* parent = nullptr);

  ~About() override = default;
};
