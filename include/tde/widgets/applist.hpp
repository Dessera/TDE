#pragma once

#include <qgridlayout.h>
#include <qstackedwidget.h>
#include <qtmetamacros.h>
#include <qwidget.h>

#include "tde/helpers/appfetcher.hpp"
#include "tde/settings.hpp"

namespace tde::widgets {

class AppListCard : public QWidget
{
  Q_OBJECT

private:
  QSize _grid_size;

public:
  AppListCard(const QSize& grid_size, QWidget* parent = nullptr);
  ~AppListCard() override = default;

  /**
   * @brief Adds an app to the card
   *
   * @param app AppItem pointer
   */
  void add_app(const helpers::AppInfo& app);

  /**
   * @brief Returns the number of apps in the card
   *
   * @return int Number of apps
   */
  [[nodiscard]] constexpr auto app_count() const { return layout()->count(); }

  /**
   * @brief Returns the size of the app grid
   *
   * @return int Size of the app grid
   */
  [[nodiscard]] constexpr auto app_size() const
  {
    return _grid_size.width() * _grid_size.height();
  }

  [[nodiscard]] constexpr auto is_full() const
  {
    return app_count() >= app_size();
  }
};

class AppList : public QWidget
{
  Q_OBJECT

private:
  QSize _grid_size;
  QStackedWidget* _stack;
  QList<AppListCard*> _cards;

public:
  AppList(const AppSettings& settings, QWidget* parent = nullptr);
  ~AppList() override = default;

private:
  void _init(const AppSettings& settings);
  void _init_ui(const AppSettings& settings);

  void _create_card();
  void _clean_cards();

public slots:
  void on_apps_changed(const QList<helpers::AppInfo>& apps);
};
}
