/**
 * @file container.hpp
 * @author Dessera (dessera@qq.com)
 * @brief TDE application wrapper.
 * @version 0.1.0
 * @date 2025-07-09
 *
 * @copyright Copyright (c) 2025 Dessera
 *
 */

#pragma once

#include <qboxlayout.h>
#include <qstring.h>
#include <qwidget.h>
#include <type_traits>

#include "tde/assets/styles.hpp"
#include "tde/common.hpp"
#include "tde/settings.hpp"

namespace tde::widgets::app {

/**
 * @brief TDE application wrapper.
 *
 */
class TDE_PUBLIC Container : public QWidget
{
  Q_OBJECT

public:
  using StyleScope = assets::styles::Scope;

  /**
   * @brief Construct a new Container object.
   *
   * @param parent Parent widget.
   */
  Container(StyleScope scope,
            const QString& name,
            bool decoration,
            DesktopSettings* settings,
            QWidget* root,
            QWidget* parent = nullptr);

  ~Container() override = default;
};

}
