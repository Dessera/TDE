#include <qapplication.h>
#include <qboxlayout.h>
#include <qlabel.h>
#include <qtoolbutton.h>

#include "tde/widgets/app/decoration.hpp"

namespace tde::widgets::app {

Decoration::Decoration(const QString& app_name, QWidget* parent)
  : QWidget{ parent }
{
  setProperty("class", "tde-app-decoration");
  setAttribute(Qt::WA_StyledBackground, true);

  auto* layout = new QHBoxLayout{ this };
  setLayout(layout);

  auto* app_name_label = new QLabel{ app_name, this };
  app_name_label->setProperty("class", "tde-app-decoration-text");
  layout->addWidget(app_name_label);

  layout->addStretch(1);

  auto* close_btn = new QToolButton{ this };
  close_btn->setProperty(
    "class", "tde-app-decoration-button tde-app-decoration-close-button");
  layout->addWidget(close_btn);

  connect(close_btn,
          &QToolButton::clicked,
          this,
          &Decoration::_on_close_button_clicked);
}

void
Decoration::_on_close_button_clicked()
{
  QApplication::quit();
}

}
