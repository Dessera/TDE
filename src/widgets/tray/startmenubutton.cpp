#include "tde/widgets/tray/startmenubutton.hpp"

namespace tde::widgets::tray {

StartMenuButton::StartMenuButton(QWidget* parent)
  : QToolButton{ parent }
{
  setProperty("class", "tde-tray-startmenu-button");
  setText("Start");
  setIcon(QIcon{ StartMenuIcon });
  setIconSize({ StartMenuIconSize, StartMenuIconSize });
}

}
