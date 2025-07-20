#include <qapplication.h>
#include <qboxlayout.h>
#include <qlabel.h>
#include <qtoolbutton.h>

#include "tde/widgets/app/decoration.hpp"
#include "tde/widgets/text/header.hpp"

namespace tde::widgets::app {

Decoration::Decoration(const QString& app_name, QWidget* parent)
  : QWidget{ parent }
{
  setAttribute(Qt::WA_StyledBackground, true);

  auto* layout = new QHBoxLayout{ this };
  setLayout(layout);

  layout->addWidget(new text::H6{ app_name, this });

  layout->addStretch(1);

  auto* close_btn = new QToolButton{ this };
  close_btn->setProperty("class", "tde-close-button");
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
