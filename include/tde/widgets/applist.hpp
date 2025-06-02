/**
 * @file applist.hpp
 * @author Dessera (dessera@qq.com)
 * @brief Application list widget
 * @version 0.1.0
 * @date 2025-06-02
 *
 * @copyright Copyright (c) 2025 Dessera
 *
 */

#pragma once

#include <qgridlayout.h>
#include <qstackedwidget.h>
#include <qtmetamacros.h>
#include <qwidget.h>

#include "tde/helpers/appfetcher.hpp"
#include "tde/settings.hpp"

namespace tde::widgets {

/**
 * @brief Application list card.
 *
 */
class AppListCard : public QWidget
{
  Q_OBJECT

private:
  QSize _grid_size;

public:
  /**
   * @brief Construct a new App List Card object.
   *
   * @param grid_size Size of the app grid.
   * @param parent Parent widget
   */
  AppListCard(const QSize& grid_size, QWidget* parent = nullptr);
  ~AppListCard() override = default;

  /**
   * @brief Adds an app to the card.
   *
   * @param app Application information.
   */
  void add_app(const helpers::AppInfo& app);

  /**
   * @brief Returns the number of apps in the card.
   *
   * @return int Number of apps.
   */
  [[nodiscard]] constexpr auto app_count() const { return layout()->count(); }

  /**
   * @brief Returns the size of the app grid.
   *
   * @return int Size of the app grid.
   */
  [[nodiscard]] constexpr auto app_size() const
  {
    return _grid_size.width() * _grid_size.height();
  }

  /**
   * @brief Checks if the card is full.
   *
   * @return bool True if the card is full, false otherwise.
   */
  [[nodiscard]] constexpr auto is_full() const
  {
    return app_count() >= app_size();
  }

signals:
  /**
   * @brief Emitted when the app is requested to be launched.
   *
   * @param app Application info.
   */
  void request_launch_app(const helpers::AppInfo& app);
};

/**
 * @brief Application list widget, which is a group of AppListCard.
 *
 */
class AppList : public QWidget
{
  Q_OBJECT

private:
  QSize _grid_size;
  QStackedWidget* _stack;

public:
  /**
   * @brief Construct a new App List object.
   *
   * @param settings Desktop settings.
   * @param parent Parent widget.
   */
  AppList(const DesktopSettings& settings, QWidget* parent = nullptr);
  ~AppList() override = default;

private:
  /**
   * @brief Initializes the widget.
   *
   * @param settings Desktop settings.
   */
  void _init(const DesktopSettings& settings);

  /**
   * @brief Initializes the UI components.
   *
   * @param settings Desktop settings.
   */
  void _init_ui(const DesktopSettings& settings);

  /**
   * @brief Creates a new card.
   *
   */
  void _create_card();

signals:
  /**
   * @brief Emitted when the app is requested to be launched.
   *
   * @param app Application info.
   */
  void request_launch_app(const helpers::AppInfo& app);

public slots:
  /**
   * @brief Handles the apps changed signal.
   *
   * @param apps List of apps.
   */
  void on_apps_changed(const QList<helpers::AppInfo>& apps);
};

}
