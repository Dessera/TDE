#include <qstackedlayout.h>

#include "tde/settings.hpp"
#include "tde/widgets/appitem.hpp"
#include "tde/widgets/applist.hpp"

namespace tde::widgets {

AppList::AppList(const AppSettings& settings, QWidget* parent)
  : QWidget(parent)
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
AppList::_init_ui(const AppSettings& settings)
{
  auto* layout = new QStackedLayout{ this };
  setLayout(layout);

  layout->addWidget(new AppListCard{ settings, this });

  auto card_size = settings.desktop_grid();
  auto card_count = card_size.width() * card_size.height();

  int apps = 7;
  for (int i = 0; i < apps; ++i) {
    auto* cw = dynamic_cast<AppListCard*>(layout->currentWidget());
    cw->add_app(new AppItem{ QIcon(":/icons/default-icon.svg"), "app", this });
    if (cw->app_count() >= card_count) {
      layout->addWidget(new AppListCard{ settings, this });
    }
  }

  layout->setCurrentIndex(0);
}

AppListCard::AppListCard(const AppSettings& settings, QWidget* parent)
  : QWidget(parent)
  , _grid_size(settings.desktop_grid())
{
  _init(settings);
  _init_ui(settings);
}

void
AppListCard::add_app(AppItem* app)
{
  auto* layout = dynamic_cast<QGridLayout*>(this->layout());
  int current_count = app_count();
  layout->addWidget(app,
                    current_count / _grid_size.width(),
                    current_count % _grid_size.width());
}

int
AppListCard::app_count() const
{
  auto* layout = dynamic_cast<QGridLayout*>(this->layout());
  return layout->count();
}

void
AppListCard::_init(const AppSettings& /*settings*/)
{
  setProperty("class", "tde-app-list-card");
}

void
AppListCard::_init_ui(const AppSettings& /*settings*/)
{
  auto* layout = new QGridLayout{ this };
  setLayout(layout);
}

}
