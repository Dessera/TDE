/**
 * @file dock.hpp
 * @author Dessera (dessera@qq.com)
 * @brief Dock widget
 * @version 0.1.0
 * @date 2025-06-02
 *
 * @copyright Copyright (c) 2025 Dessera
 *
 */

#pragma once

#include <qlist.h>
#include <qtmetamacros.h>
#include <qwidget.h>

#include "tde/helpers/appfetcher.hpp"
#include "tde/settings.hpp"

namespace tde::widgets {

/**
 * @brief Dock widget
 *
 */
class Dock : public QWidget
{
  Q_OBJECT

public:
  /**
   * @brief Construct a new Dock object.
   *
   * @param settings Desktop settings.
   * @param parent Parent widget.
   */
  Dock(const DesktopSettings& settings, QWidget* parent = nullptr);
  ~Dock() override = default;

private:
  /**
   * @brief Initialize the dock.
   *
   * @param settings Desktop settings.
   */
  void _init(const DesktopSettings& settings);

  /**
   * @brief Initialize the UI components.
   *
   * @param settings Desktop settings.
   */
  void _init_ui(const DesktopSettings& settings);

public slots:
  /**
   * @brief Handle the dock apps changed signal.
   *
   * @param apps List of apps.
   */
  void on_dock_apps_changed(const QList<helpers::AppInfo>& apps);
};

}
