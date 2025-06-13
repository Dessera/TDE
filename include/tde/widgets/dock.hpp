/**
 * @file dock.hpp
 * @author Dessera (dessera@qq.com)
 * @brief Dock widget.
 * @version 0.1.0
 * @date 2025-06-02
 *
 * @copyright Copyright (c) 2025 Dessera
 *
 */

#pragma once

#include <qlist.h>
#include <qwidget.h>

#include "tde/app/info.hpp"
#include "tde/common.hpp"
#include "tde/widgets/appitem.hpp"

namespace tde::widgets {

/**
 * @brief Dock widget
 *
 */
class TDE_EXPORT Dock : public QWidget
{
  Q_OBJECT

private:
  QList<AppItem*> _dock_apps;

public:
  /**
   * @brief Construct a new Dock object.
   *
   * @param parent Parent widget.
   */
  Dock(QWidget* parent = nullptr);
  ~Dock() override = default;

private:
  /**
   * @brief Initialize the dock.
   *
   */
  void _init();

  /**
   * @brief Initialize the UI components.
   *
   */
  void _init_ui();

  /**
   * @brief Create the app item.
   *
   * @param app Application info.
   */
  void _create_app(const app::Info& app);

  /**
   * @brief Clear the dock apps.
   *
   */
  void _clear_apps();

signals:
  /**
   * @brief Emitted when the app is requested to be launched.
   *
   * @param app Application info.
   */
  void request_launch_app(const app::Info& app);

public slots:
  /**
   * @brief Handle the dock apps changed signal.
   *
   * @param apps List of apps.
   */
  void on_dock_apps_changed(const QList<app::Info>& apps);
};

}
