#include "tde/widgets/tray/startmenubutton.hpp"

namespace tde::widgets::tray {

StartMenuButton::StartMenuButton(QWidget* parent)
  : QToolButton{ parent }
  , _start_menu(new StartMenu{ this })
{
  setProperty("class", "tde-tray-startmenu-button");

  setText("Start");
  setIcon(QIcon{ StartMenuIcon });
  setIconSize({ StartMenuIconSize, StartMenuIconSize });

  connect(this, &QToolButton::released, this, &StartMenuButton::_on_released);
}

void
StartMenuButton::_on_released()
{
  _start_menu->show();
}

}
