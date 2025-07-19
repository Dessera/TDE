/**
 * @file buildinfo.hpp
 * @author Dessera (dessera@qq.com)
 * @brief Build info page.
 * @version 0.1.0
 * @date 2025-07-19
 *
 * @copyright Copyright (c) 2025 Dessera
 *
 */

#pragma once

#include <qwidget.h>

/**
 * @brief Build info page.
 *
 */
class BuildInfo : public QWidget
{
  Q_OBJECT

public:
  /**
   * @brief Construct a new Build Info object.
   *
   * @param parent Parent widget.
   */
  explicit BuildInfo(QWidget* parent = nullptr);

  ~BuildInfo() override = default;
};
