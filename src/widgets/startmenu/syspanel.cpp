#include <qboxlayout.h>
#include <qlabel.h>
#include <qlayoutitem.h>
#include <qwidget.h>

#include "tde/widgets/startmenu/syspanel.hpp"

namespace tde::widgets::startmenu {

SysPanel::SysPanel(QWidget* parent)
  : QWidget{ parent }
{
  setProperty("class", "tde-startmenu-sys-panel");

  auto* layout = new QVBoxLayout{ this };
  setLayout(layout);

  layout->addWidget(new QLabel{ "Linux", this });
  layout->addSpacerItem(
    new QSpacerItem{ 0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding });
}

}
