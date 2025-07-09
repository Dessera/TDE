#include <qboxlayout.h>
#include <qlabel.h>

#include "tde/widgets/app/decoration.hpp"

namespace tde::widgets::app {

Decoration::Decoration(const QString& app_name, QWidget* parent)
  : QWidget{ parent }
{
  setProperty("class", "tde-app-decoration");
  setAttribute(Qt::WA_StyledBackground, true);

  auto* layout = new QHBoxLayout{ this };
  setLayout(layout);

  layout->addWidget(new QLabel{ app_name, this });
  layout->addStretch(1);
  layout->addWidget(new QLabel{ "X", this });
}

}
