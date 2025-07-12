#include <algorithm>
#include <qboxlayout.h>
#include <qlogging.h>
#include <qstackedwidget.h>
#include <qwidget.h>

#include "tde/widgets/app/button.hpp"
#include "tde/widgets/app/card.hpp"
#include "tde/widgets/radioselector.hpp"

namespace tde::widgets::app {

Card::Card(const QSize& grid_size, QWidget* parent)
  : QWidget{ parent }
  , _grid_size{ grid_size }
{
  setProperty("class", "tde-app-card");

  auto* layout = new QGridLayout{ this };
  setLayout(layout);
}

void
Card::add_app(const AppInfo& app)
{
  int curr = app_count();
  if (curr >= app_size()) {
    qWarning() << "Failed to add app to card: card is full";
    return;
  }

  auto* layout = qobject_cast<QGridLayout*>(this->layout());

  auto* app_btn = new Button{ app, this };
  connect(
    app_btn, &Button::request_launch_app, this, &Card::request_launch_app);
  layout->addWidget(
    app_btn, curr / _grid_size.width(), curr % _grid_size.width());
}

CardList::CardList(const QSize& grid_size, QWidget* parent)
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

  connect(_sel, &RadioSelector::selected, this, &CardList::_on_selected);
}

void
CardList::_create_card()
{
  auto* card = new Card{ _grid_size, this };
  connect(card, &Card::request_launch_app, this, &CardList::request_launch_app);

  _stack->addWidget(card);
  _cards.push_back(card);
}

void
CardList::_clear_cards()
{
  for (auto* card : _cards) {
    _stack->removeWidget(card);
    card->deleteLater();
  }

  _cards.clear();
}

void
CardList::on_apps_changed(const QList<Card::AppInfo>& apps)
{
  auto old_idx = std::max(_stack->currentIndex(), 0);
  int new_idx = 0;

  _clear_cards();

  _create_card();
  for (const auto& app : apps) {
    auto* cw = qobject_cast<Card*>(_stack->widget(new_idx));
    if (cw->is_full()) {
      _create_card();
      new_idx++;
      cw = qobject_cast<Card*>(_stack->widget(new_idx));
    }
    cw->add_app(app);
  }

  auto next_idx = std::min(old_idx, new_idx);
  _stack->setCurrentIndex(next_idx);

  _sel->set_count(_stack->count());
  _sel->set_current(next_idx);
}

void
CardList::_on_selected(int index)
{
  if (index < 0 || index >= _stack->count()) {
    qWarning() << "Invalid index when selecting app list card:" << index;
    return;
  }

  _stack->setCurrentIndex(index);
}

}
