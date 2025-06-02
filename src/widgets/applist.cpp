#include <qboxlayout.h>
#include <qicon.h>
#include <qlabel.h>
#include <qlogging.h>
#include <qstackedwidget.h>
#include <qwidget.h>

#include "tde/helpers/appfetcher.hpp"
#include "tde/settings.hpp"
#include "tde/widgets/appitem.hpp"
#include "tde/widgets/applist.hpp"

namespace tde::widgets {

AppList::AppList(const DesktopSettings& settings, QWidget* parent)
  : QWidget(parent)
  , _grid_size(QSize{ settings.desktop_grid_x(), settings.desktop_grid_y() })
  , _stack(new QStackedWidget{ this })
{
  _init(settings);
  _init_ui(settings);
}

void
AppList::_init(const DesktopSettings& /*settings*/)
{
  setProperty("class", "tde-app-list");
}

void
AppList::_init_ui(const DesktopSettings& /*settings*/)
{
  auto* layout = new QVBoxLayout{ this };
  setLayout(layout);

  layout->addWidget(_stack, 1);
  layout->addWidget(new QLabel{ "More", this }, 0, Qt::AlignHCenter);
}

void
AppList::_create_card()
{
  _cards.push_back(new AppListCard{ _grid_size, this });
  _stack->addWidget(_cards.back());
}

void
AppList::_clean_cards()
{
  for (auto* card : _cards) {
    _stack->removeWidget(card);
    delete card;
  }
  _cards.clear();
}

void
AppList::on_apps_changed(const QList<helpers::AppInfo>& apps)
{
  auto old_idx = _stack->currentIndex();

  _clean_cards();
  _create_card();

  for (const auto& app : apps) {
    auto* cw = dynamic_cast<AppListCard*>(_stack->currentWidget());
    cw->add_app(app);
    if (cw->is_full()) {
      _create_card();
    }
  }

  auto curr_size = _stack->count();
  _stack->setCurrentIndex(std::min(old_idx, curr_size - 1));
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
AppListCard::add_app(const helpers::AppInfo& app)
{
  int curr = app_count();
  if (curr >= app_size()) {
    qWarning() << "AppListCard is full, cannot add more apps";
    return;
  }

  auto* layout = dynamic_cast<QGridLayout*>(this->layout());

  // TODO: A Factory for AppItem
  layout->addWidget(new AppItem{ QIcon{ app.icon }, app.name, this },
                    curr / _grid_size.width(),
                    curr % _grid_size.width());
}

}
