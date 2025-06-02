/**
 * @file appitem.hpp
 * @author Dessera (dessera@qq.com)
 * @brief Application item widget
 * @version 0.1.0
 * @date 2025-06-02
 *
 * @copyright Copyright (c) 2025 Dessera
 *
 */

#pragma once

#include <qicon.h>
#include <qtmetamacros.h>
#include <qtoolbutton.h>

namespace tde::widgets {

/**
 * @brief Application item widget.
 *
 */
class AppItem : public QToolButton
{
  Q_OBJECT

public:
  constexpr static int IconSize =
    48; /**< Default icon size, which is immutable now. */

  /**
   * @brief Construct a new App Item object.
   *
   * @param icon Icon of the application.
   * @param name Name of the application.
   * @param parent Parent widget
   */
  AppItem(const QIcon& icon, const QString& name, QWidget* parent = nullptr);
  ~AppItem() override = default;
};

}
