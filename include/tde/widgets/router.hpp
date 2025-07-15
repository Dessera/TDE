/**
 * @file router.hpp
 * @author Dessera (dessera@qq.com)
 * @brief Standard widget router.
 * @version 0.1.0
 * @date 2025-07-15
 *
 * @copyright Copyright (c) 2025 Dessera
 *
 */

#pragma once

#include <qmap.h>
#include <qstackedwidget.h>
#include <qstring.h>
#include <qtoolbutton.h>
#include <qwidget.h>

#include "tde/common.hpp"

namespace tde::widgets {

/**
 * @brief TDE standard widget router menu.
 *
 */
class TDE_PUBLIC RouterMenu : public QWidget
{
  Q_OBJECT

public:
  /**
   * @brief Router menu item.
   *
   */
  struct Item
  {
    QString name;
    QIcon icon;
  };

  /**
   * @brief Construct a new Router Menu object.
   *
   * @param parent Parent widget.
   */
  RouterMenu(QWidget* parent = nullptr);

  ~RouterMenu() override = default;

  /**
   * @brief Add a new item to the menu.
   *
   * @param item Item to add.
   */
  void add(const Item& item);

  /**
   * @brief Remove an item from the menu.
   *
   * @param name Name of the item to remove.
   */
  void remove(const QString& name);

  /**
   * @brief Clear all items from the menu.
   *
   */
  void clear();

private:
  /**
   * @brief Create a new button for the menu.
   *
   * @param item Item to create button for.
   * @return QToolButton* Created button.
   */
  QToolButton* _create_button(const Item& item);

signals:
  /**
   * @brief Emitted when a button is clicked.
   *
   * @param name Name of the button that was clicked.
   */
  void clicked(const QString& name);

private slots:
  /**
   * @brief Handles button click events.
   *
   */
  void _on_button_clicked();
};

/**
 * @brief TDE standard widget router.
 *
 */
class TDE_PUBLIC Router : public QWidget
{
  Q_OBJECT

private:
  RouterMenu* _rlinks;
  QStackedWidget* _rviews;

  QMap<QString, QWidget*> _view_map;

public:
  /**
   * @brief Construct a new Router object.
   *
   * @param parent Parent widget.
   */
  Router(QWidget* parent = nullptr);

  ~Router() override = default;

  /**
   * @brief Add a new view to the router.
   *
   * @param item Menu item for the view.
   * @param view View to add.
   */
  void add(const RouterMenu::Item& item, QWidget* view);

  /**
   * @brief Remove a view from the router.
   *
   * @param name Name of the view to remove.
   */
  void remove(const QString& name);

  /**
   * @brief Clear all views from the router.
   *
   */
  void clear();

  /**
   * @brief Set the current view.
   *
   * @param name Name of the view to set.
   */
  void set_current_view(const QString& name);

private slots:
  /**
   * @brief Handles menu item click events.
   *
   * @param name Name of the menu item that was clicked.
   */
  void _on_rlinks_clicked(const QString& name);
};

}
