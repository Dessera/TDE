/**
 * @file card.hpp
 * @author Dessera (dessera@qq.com)
 * @brief Application card.
 * @version 0.1.0
 * @date 2025-06-02
 *
 * @copyright Copyright (c) 2025 Dessera
 *
 */

#pragma once

#include <qgridlayout.h>
#include <qstackedwidget.h>
#include <qwidget.h>

#include "tde/app/info.hpp"
#include "tde/common.hpp"
#include "tde/widgets/radioselector.hpp"

namespace tde::widgets::app {

/**
 * @brief Application list card.
 *
 */
class TDE_PUBLIC Card : public QWidget
{
  Q_OBJECT

public:
  using AppInfo = tde::app::Info;

private:
  QSize _grid_size;

public:
  /**
   * @brief Construct a new App Card object.
   *
   * @param grid_size Size of the app grid.
   * @param parent Parent widget.
   */
  Card(const QSize& grid_size, QWidget* parent = nullptr);

  ~Card() override = default;

  /**
   * @brief Adds an app to the card.
   *
   * @param app Application information.
   */
  void add_app(const AppInfo& app);

  /**
   * @brief Returns the number of apps in the card.
   *
   * @return int Number of apps.
   */
  [[nodiscard]] TDE_INLINE auto app_count() const { return layout()->count(); }

  /**
   * @brief Returns the size of the app grid.
   *
   * @return int Size of the app grid.
   */
  [[nodiscard]] TDE_INLINE auto app_size() const
  {
    return _grid_size.width() * _grid_size.height();
  }

  /**
   * @brief Checks if the card is full.
   *
   * @return bool True if the card is full, false otherwise.
   */
  [[nodiscard]] TDE_INLINE auto is_full() const
  {
    return app_count() >= app_size();
  }

signals:
  /**
   * @brief Emitted when the app is requested to be launched.
   *
   * @param app Application info.
   */
  void request_launch_app(const AppInfo& app);
};

/**
 * @brief Application list widget, which is a group of AppCard.
 *
 */
class TDE_PUBLIC CardList : public QWidget
{
  Q_OBJECT

private:
  QSize _grid_size;
  QList<Card*> _cards;
  QStackedWidget* _stack;
  RadioSelector* _sel;

public:
  /**
   * @brief Construct a new App Card List object.
   *
   * @param grid_size Size of the app grid.
   * @param parent Parent widget.
   */
  CardList(const QSize& grid_size, QWidget* parent = nullptr);

  ~CardList() override = default;

private:
  /**
   * @brief Creates a new card.
   *
   */
  void _create_card();

  /**
   * @brief Clears all cards.
   *
   */
  void _clear_cards();

signals:
  /**
   * @brief Emitted when the app is requested to be launched.
   *
   * @param app Application info.
   */
  void request_launch_app(const Card::AppInfo& app);

public slots:
  /**
   * @brief Handles the apps changed signal.
   *
   * @param apps List of apps.
   */
  void on_apps_changed(const QList<Card::AppInfo>& apps);

private slots:
  /**
   * @brief Handles the selected card changed signal.
   *
   * @param index Index of the selected card.
   */
  void _on_selected(int index);
};

}
