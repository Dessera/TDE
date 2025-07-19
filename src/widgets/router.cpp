#include <qboxlayout.h>
#include <qdebug.h>
#include <qtoolbutton.h>

#include "tde/widgets/router.hpp"

namespace tde::widgets {

RouterMenu::RouterMenu(QWidget* parent)
  : QWidget{ parent }
{
  setProperty("class", "tde-router-menu");
  setAttribute(Qt::WA_StyledBackground, true);

  auto* layout = new QVBoxLayout{ this };
  layout->setSpacing(5);
  setLayout(layout);

  layout->addStretch(1);
}

void
RouterMenu::add(const Item& item)
{
  auto* button = _create_button(item);
  connect(button, &QToolButton::clicked, this, &RouterMenu::_on_button_clicked);

  auto* _layout = qobject_cast<QVBoxLayout*>(layout());
  auto index = _layout->count() - 1;

  _layout->insertWidget(index, button);
}

void
RouterMenu::remove(const QString& name)
{
  for (auto* button : findChildren<QToolButton*>(Qt::FindDirectChildrenOnly)) {
    if (button->text() == name) {
      layout()->removeWidget(button);
      button->deleteLater();
      return;
    }
  }
}

void
RouterMenu::clear()
{
  for (auto* button : findChildren<QToolButton*>(Qt::FindDirectChildrenOnly)) {
    layout()->removeWidget(button);
    button->deleteLater();
  }
}

QToolButton*
RouterMenu::_create_button(const Item& item)
{
  auto* button = new QToolButton{ this };

  button->setText(item.name);
  button->setIcon(item.icon);

  return button;
}

void
RouterMenu::_on_button_clicked()
{
  auto* button = qobject_cast<QToolButton*>(sender());

  if (button == nullptr) {
    qWarning() << "Failed to emit router button clicked: invalid sender";
    return;
  }

  emit clicked(button->text());
}

Router::Router(QWidget* parent)
  : QWidget{ parent }
  , _rlinks{ new RouterMenu{ this } }
  , _rviews{ new QStackedWidget{ this } }
{
  setProperty("class", "tde-router");

  auto* layout = new QHBoxLayout{ this };
  layout->setContentsMargins(0, 0, 0, 0);
  setLayout(layout);

  connect(_rlinks, &RouterMenu::clicked, this, &Router::_on_rlinks_clicked);

  layout->addWidget(_rlinks);
  layout->addWidget(_rviews, 1);
}

void
Router::add(const RouterMenu::Item& item, QWidget* view)
{
  _rlinks->add(item);
  _rviews->addWidget(view);

  _view_map.insert(item.name, view);
}

void
Router::remove(const QString& name)
{
  if (_view_map.contains(name)) {
    _rlinks->remove(name);
    _rviews->removeWidget(_view_map[name]);
  }
}

void
Router::clear()
{
  for (auto* view : _view_map) {
    _rviews->removeWidget(view);
  }

  _view_map.clear();
  _rlinks->clear();
}

void
Router::set_current_view(const QString& name)
{
  if (!_view_map.contains(name)) {
    qWarning() << "Failed to switch to view: invalid name";
    return;
  }

  _rviews->setCurrentWidget(_view_map[name]);
}

void
Router::_on_rlinks_clicked(const QString& name)
{
  set_current_view(name);
}

}
