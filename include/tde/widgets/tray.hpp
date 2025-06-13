/**
 * @file tray.hpp
 * @author Dessera (dessera@qq.com)
 * @brief Tray widget.
 * @version 0.1.0
 * @date 2025-06-09
 *
 * @copyright Copyright (c) 2025 Dessera
 *
 */

#pragma once

#include <qwidget.h>

#include "tde/common.hpp"
#include "tde/settings.hpp"

namespace tde::widgets {

/**
 * @brief Tray widget.
 *
 */
class TDE_EXPORT Tray : public QWidget
{
  Q_OBJECT

public:
  /**
   * @brief Construct a new Tray object.
   *
   * @param settings Desktop settings.
   * @param parent Parent widget.
   */
  Tray(const DesktopSettings& settings, QWidget* parent = nullptr);
  ~Tray() override = default;

private:
  /**
   * @brief Initialize the tray.
   *
   * @param settings Desktop settings.
   */
  void _init(const DesktopSettings& settings);

  /**
   * @brief Initialize the tray UI components.
   *
   * @param settings Desktop settings.
   */
  void _init_ui(const DesktopSettings& settings);
};

}
