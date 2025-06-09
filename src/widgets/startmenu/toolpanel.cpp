#include <qboxlayout.h>
#include <qlayoutitem.h>
#include <qwidget.h>

#include "tde/widgets/startmenu/toolbutton.hpp"
#include "tde/widgets/startmenu/toolpanel.hpp"

namespace tde::widgets::startmenu {

ToolPanel::ToolPanel(QWidget* parent)
  : QWidget{ parent }
{
  setProperty("class", "tde-startmenu-tool-panel");

  auto* layout = new QVBoxLayout{ this };
  setLayout(layout);

  layout->addSpacerItem(
    new QSpacerItem{ 0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding });

  for (const auto& tool : Tools) {
    layout->addWidget(new ToolButton{ tool, this });
  }
}

}
