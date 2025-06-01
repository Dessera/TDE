#pragma once

#include <qtmetamacros.h>
#include <qwidget.h>

#include "tde/settings.hpp"
#include "tde/widgets/appitem.hpp"

namespace tde::widgets {

class AppList : public QWidget
{
  Q_OBJECT

public:
  AppList(const AppSettings& settings, QWidget* parent = nullptr);
  ~AppList() override = default;

private:
  void _init(const AppSettings& settings);
  void _init_ui(const AppSettings& settings);
};

class AppListCard : public QWidget
{
  Q_OBJECT

private:
  QSize _grid_size;

public:
  AppListCard(const AppSettings& settings, QWidget* parent = nullptr);
  ~AppListCard() override = default;

  void add_app(AppItem* app);
  [[nodiscard]] int app_count() const;

private:
  void _init(const AppSettings& settings);
  void _init_ui(const AppSettings& settings);
};

}
