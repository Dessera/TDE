/**
 * @file desktop.hpp
 * @author Dessera (dessera@qq.com)
 * @brief Desktop widget
 * @version 0.1.0
 * @date 2025-06-02
 *
 * @copyright Copyright (c) 2025 Dessera
 *
 */

#pragma once

#include <qlist.h>
#include <qwidget.h>

#include "tde/helpers/appfetcher.hpp"
#include "tde/settings.hpp"

namespace tde::widgets {

/**
 * @brief Desktop widget, which is the root of UI.
 *
 */
class Desktop : public QWidget
{
  Q_OBJECT

public:
  constexpr static int DockMargin = 5; /**< Margin for dock widget. */

  /**
   * @brief Construct a new Desktop object.
   *
   * @param settings Desktop settings.
   * @param parent Parent widget.
   */
  Desktop(const DesktopSettings& settings, QWidget* parent = nullptr);
  ~Desktop() override = default;

private:
  /**
   * @brief Initialize desktop.
   *
   * @param settings Desktop settings.
   */
  void _init(const DesktopSettings& settings);

  /**
   * @brief Initialize UI components.
   *
   * @param settings Desktop settings.
   */
  void _init_ui(const DesktopSettings& settings);

signals:
  /**
   * @brief Emitted when apps changed.
   *
   * @param apps List of apps.
   */
  void apps_changed(const QList<helpers::AppInfo>& apps);

  /**
   * @brief Emitted when dock apps changed.
   *
   * @param apps List of dock apps.
   */
  void dock_apps_changed(const QList<helpers::AppInfo>& apps);
};

}
