/**
 * @file appitem.hpp
 * @author Dessera (dessera@qq.com)
 * @brief Application item widget.
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

#include "tde/helpers/appfetcher.hpp"

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

private:
  QString _exec;

public:
  /**
   * @brief Construct a new App Item object.
   *
   * @param app Application info.
   * @param parent Parent widget.
   */
  AppItem(const helpers::AppInfo& app, QWidget* parent = nullptr);
  ~AppItem() override = default;

  [[nodiscard]] constexpr auto& exec() const { return _exec; }

signals:
  /**
   * @brief Emitted when the app is requested to be launched.
   *
   * @param app Application info.
   */
  void request_launch_app(const helpers::AppInfo& app);

private slots:
  /**
   * @brief Emits request_launch_app signal when the button is released.
   *
   */
  void on_released();
};

/**
 * @brief Application item factory.
 *
 */
class AppItemFactory
{
public:
  /**
   * @brief Create a new App Item.
   *
   * @param app Application info.
   * @param parent Parent widget.
   * @param style Tool button style.
   * @return AppItem* Created App Item.
   */
  static AppItem* create(
    const helpers::AppInfo& app,
    QWidget* parent,
    Qt::ToolButtonStyle style = Qt::ToolButtonTextUnderIcon);

  /**
   * @brief Create AppInfo from AppItem.
   *
   * @param item AppItem.
   * @return helpers::AppInfo AppInfo.
   */
  static helpers::AppInfo create_app_info(const AppItem* item);
};

}
