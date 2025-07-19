#include <algorithm>
#include <qboxlayout.h>
#include <qradiobutton.h>

#include "tde/widgets/radioselector.hpp"

namespace tde::widgets {

RadioSelector::RadioSelector(QWidget* parent)
  : QWidget{ parent }
{
  setProperty("class", "tde-radio-selector");

  auto* layout = new QHBoxLayout{ this };
  setLayout(layout);
}

void
RadioSelector::_create_button()
{
  auto* button = new QRadioButton{ this };

  connect(
    button, &QRadioButton::clicked, this, &RadioSelector::on_button_clicked);

  layout()->addWidget(button);
  _buttons.push_back(button);
}

void
RadioSelector::_clear_buttons()
{
  for (auto* btn : _buttons) {
    layout()->removeWidget(btn);
    btn->deleteLater();
  }
  _buttons.clear();
}

void
RadioSelector::set_count(int count)
{
  _clear_buttons();

  for (int i = 0; i < count; ++i) {
    _create_button();
  }
}

void
RadioSelector::set_current(int index)
{
  if (index < 0 || index > _buttons.size()) {
    qWarning() << "Invalid selector index:" << index;
    return;
  }

  _buttons[index]->setChecked(true);
}

void
RadioSelector::on_button_clicked()
{
  auto* button = qobject_cast<QRadioButton*>(sender());

  button->setChecked(true);

  auto res = std::find(_buttons.begin(), _buttons.end(), button);
  if (res == _buttons.end()) {
    qWarning() << "Invalid button:" << button;
    return;
  }

  auto index = std::distance(_buttons.begin(), res);
  emit selected(static_cast<int>(index));
}

}
