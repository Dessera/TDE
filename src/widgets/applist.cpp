#include <qboxlayout.h>
#include <qlabel.h>
#include <qlogging.h>
#include <qstackedwidget.h>
#include <qwidget.h>

#include "qicon.h"
#include "tde/helpers/appfetcher.hpp"
#include "tde/settings.hpp"
#include "tde/widgets/appitem.hpp"
#include "tde/widgets/applist.hpp"

namespace tde::widgets {

AppList::AppList(const AppSettings& settings, QWidget* parent)
  : QWidget(parent)
  , _grid_size(settings.desktop_grid())
  , _stack(new QStackedWidget{ this })
{
  _init(settings);
  _init_ui(settings);
}

void
AppList::_init(const AppSettings& /*settings*/)
{
  setProperty("class", "tde-app-list");
}

void
AppList::_init_ui(const AppSettings& /*settings*/)
{
  auto* layout = new QVBoxLayout{ this };
  setLayout(layout);

  layout->addWidget(_stack, 1);

  _stack->addWidget(new AppListCard{ _grid_size, this });

  layout->addWidget(new QLabel{ "More", this }, 0, Qt::AlignHCenter);
}

void
AppList::on_apps_changed(const QList<helpers::AppInfo>& apps)
{
  auto apps_size = apps.size();

  for (int i = 0; i < apps_size; ++i) {
    auto* cw = dynamic_cast<AppListCard*>(_stack->currentWidget());
    cw->add_app(new AppItem{ QIcon{ apps[i].icon }, apps[i].name, this });
    if (cw->app_count() >= cw->app_size()) {
      _stack->addWidget(new AppListCard{ _grid_size, this });
    }
  }
}

AppListCard::AppListCard(const QSize& grid_size, QWidget* parent)
  : QWidget(parent)
  , _grid_size(grid_size)
{
  setProperty("class", "tde-app-list-card");

  auto* layout = new QGridLayout{ this };
  setLayout(layout);
}

void
AppListCard::add_app(AppItem* app)
{
  int curr = app_count();
  if (curr >= app_size()) {
    qWarning() << "AppListCard is full, cannot add more apps";
    return;
  }

  auto* layout = dynamic_cast<QGridLayout*>(this->layout());
  layout->addWidget(app, curr / _grid_size.width(), curr % _grid_size.width());
}

}
