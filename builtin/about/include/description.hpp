/**
 * @file description.hpp
 * @author Dessera (dessera@qq.com)
 * @brief Description page.
 * @version 0.1.0
 * @date 2025-07-19
 *
 * @copyright Copyright (c) 2025 Dessera
 *
 */

#pragma once

#include <qwidget.h>

/**
 * @brief Description page.
 *
 */
class Description : public QWidget
{
  Q_OBJECT

public:
  /**
   * @brief Construct a new Description object.
   *
   * @param parent Parent widget.
   */
  explicit Description(QWidget* parent = nullptr);

  ~Description() override = default;
};
