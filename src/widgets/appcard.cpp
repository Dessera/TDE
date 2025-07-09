#include <algorithm>
#include <qboxlayout.h>
#include <qlogging.h>
#include <qstackedwidget.h>
#include <qwidget.h>

#include "tde/app/info.hpp"
#include "tde/widgets/appbutton.hpp"
#include "tde/widgets/appcard.hpp"
#include "tde/widgets/radioselector.hpp"

namespace tde::widgets {

AppCard::AppCard(const QSize& grid_size, QWidget* parent)
  : QWidget{ parent }
  , _grid_size{ grid_size }
{
  setProperty("class", "tde-app-card");

  auto* layout = new QGridLayout{ this };
  setLayout(layout);
}

void
AppCard::add_app(const app::Info& app)
{
  int curr = app_count();
  if (curr >= app_size()) {
    qWarning() << "Failed to add app to card: card is full";
    return;
  }

  auto* layout = qobject_cast<QGridLayout*>(this->layout());

  auto* app_btn = new AppButton{ app, this };
  connect(app_btn,
          &AppButton::request_launch_app,
          this,
          &AppCard::request_launch_app);
  layout->addWidget(
    app_btn, curr / _grid_size.width(), curr % _grid_size.width());
}

AppCardList::AppCardList(const QSize& grid_size, QWidget* parent)
  : QWidget{ parent }
  , _grid_size{ grid_size }
  , _stack{ new QStackedWidget{ this } }
  , _sel{ new RadioSelector{ this } }
{
  setProperty("class", "tde-app-list");

  auto* layout = new QVBoxLayout{ this };
  setLayout(layout);

  layout->addWidget(_stack, 1);
  layout->addWidget(_sel, 0, Qt::AlignHCenter);

  connect(_sel, &RadioSelector::selected, this, &AppCardList::_on_selected);
}

void
AppCardList::_create_card()
{
  auto* card = new AppCard{ _grid_size, this };
  connect(
    card, &AppCard::request_launch_app, this, &AppCardList::request_launch_app);

  _stack->addWidget(card);
  _cards.push_back(card);
}

void
AppCardList::_clear_cards()
{
  for (auto* card : _cards) {
    _stack->removeWidget(card);
    card->deleteLater();
  }

  _cards.clear();
}

void
AppCardList::on_apps_changed(const QList<app::Info>& apps)
{
  auto old_idx = std::max(_stack->currentIndex(), 0);
  int new_idx = 0;

  _clear_cards();

  _create_card();
  for (const auto& app : apps) {
    auto* cw = qobject_cast<AppCard*>(_stack->widget(new_idx));
    if (cw->is_full()) {
      _create_card();
      new_idx++;
      cw = qobject_cast<AppCard*>(_stack->widget(new_idx));
    }
    cw->add_app(app);
  }

  auto next_idx = std::min(old_idx, new_idx);
  _stack->setCurrentIndex(next_idx);

  _sel->set_count(_stack->count());
  _sel->set_current(next_idx);
}

void
AppCardList::_on_selected(int index)
{
  if (index < 0 || index >= _stack->count()) {
    qWarning() << "Invalid index when selecting app list card:" << index;
    return;
  }

  _stack->setCurrentIndex(index);
}

}
