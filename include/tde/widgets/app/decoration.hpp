/**
 * @file decoration.hpp
 * @author Dessera (dessera@qq.com)
 * @brief Application decoration widget.
 * @version 0.1.0
 * @date 2025-07-09
 *
 * @copyright Copyright (c) 2025 Dessera
 *
 */

#pragma once

#include <qstring.h>
#include <qwidget.h>

#include "tde/common.hpp"

namespace tde::widgets::app {

/**
 * @brief Application decoration widget.
 *
 */
class TDE_PUBLIC Decoration : public QWidget
{
  Q_OBJECT

public:
  /**
   * @brief Construct a new Decoration object.
   *
   * @param app_name Application name.
   * @param parent Parent widget.
   */
  Decoration(const QString& app_name, QWidget* parent = nullptr);

  ~Decoration() override = default;
};

}
