#include <qicon.h>
#include <qtoolbutton.h>

#include "tde/startmenu.hpp"
#include "tde/widgets/startmenu/toolbutton.hpp"

namespace tde::widgets::startmenu {

ToolButton::ToolButton(const ToolInfo& info, QWidget* parent)
  : QToolButton{ parent }
{
  setProperty("class", "tde-startmenu-tool-button");

  setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

  setIcon(QIcon{ info.icon });
  setIconSize({ IconSize, IconSize });

  setText(info.name);
}

}
