#include <algorithm>
#include <qboxlayout.h>
#include <qlogging.h>
#include <qstackedwidget.h>
#include <qwidget.h>

#include "tde/app/info.hpp"
#include "tde/settings.hpp"
#include "tde/widgets/appitem.hpp"
#include "tde/widgets/applist.hpp"
#include "tde/widgets/radioselector.hpp"

namespace tde::widgets {

AppListCard::AppListCard(const QSize& grid_size, QWidget* parent)
  : QWidget(parent)
  , _grid_size(grid_size)
{
  setProperty("class", "tde-app-list-card");

  auto* layout = new QGridLayout{ this };
  setLayout(layout);
}

void
AppListCard::add_app(const app::Info& app)
{
  int curr = app_count();
  if (curr >= app_size()) {
    qWarning() << "AppListCard is full, cannot add more apps";
    return;
  }

  auto* layout = qobject_cast<QGridLayout*>(this->layout());

  auto* app_item = new AppItem{ app, this };
  connect(app_item,
          &AppItem::request_launch_app,
          this,
          &AppListCard::request_launch_app);
  layout->addWidget(
    app_item, curr / _grid_size.width(), curr % _grid_size.width());
}

AppList::AppList(const DesktopSettings& settings, QWidget* parent)
  : QWidget(parent)
  , _grid_size(QSize{ settings.desktop_grid_x(), settings.desktop_grid_y() })
  , _stack(new QStackedWidget{ this })
  , _selector(new RadioSelector{ this })
{
  _init();
  _init_ui();
}

void
AppList::_init()
{
  setProperty("class", "tde-app-list");
}

void
AppList::_init_ui()
{
  auto* layout = new QVBoxLayout{ this };
  setLayout(layout);

  layout->addWidget(_stack, 1);
  layout->addWidget(_selector, 0, Qt::AlignHCenter);

  connect(_selector, &RadioSelector::selected, this, &AppList::on_selected);
}

void
AppList::_create_card()
{
  auto* card = new AppListCard{ _grid_size, this };
  connect(
    card, &AppListCard::request_launch_app, this, &AppList::request_launch_app);
  _stack->addWidget(card);
  _cards.push_back(card);
}

void
AppList::_clear_cards()
{
  for (auto* card : _cards) {
    _stack->removeWidget(card);
    card->deleteLater();
  }
  _cards.clear();
}

void
AppList::on_apps_changed(const QList<app::Info>& apps)
{
  auto old_idx = std::max(_stack->currentIndex(), 0);
  int new_idx = 0;

  _clear_cards();

  _create_card();
  for (const auto& app : apps) {
    auto* cw = qobject_cast<AppListCard*>(_stack->widget(new_idx));
    if (cw->is_full()) {
      _create_card();
      new_idx++;
      cw = qobject_cast<AppListCard*>(_stack->widget(new_idx));
    }
    cw->add_app(app);
  }

  auto next_idx = std::min(old_idx, new_idx);
  _stack->setCurrentIndex(next_idx);

  _selector->set_count(_stack->count());
  _selector->set_current(next_idx);
}

void
AppList::on_selected(int index)
{
  if (index < 0 || index >= _stack->count()) {
    qWarning() << "Invalid index when selecting app list card:" << index;
    return;
  }

  _stack->setCurrentIndex(index);
}

}
