#include <qboxlayout.h>
#include <qtoolbutton.h>

#include "tde/widgets/tray.hpp"
#include "tde/widgets/tray/clock.hpp"
#include "tde/widgets/tray/startmenubutton.hpp"

namespace tde::widgets {

Tray::Tray(const DesktopSettings& settings, QWidget* parent)
  : QWidget{ parent }
{
  _init(settings);
  _init_ui(settings);
}

void
Tray::_init(const DesktopSettings& /*settings*/)
{
  setAttribute(Qt::WA_StyledBackground);
  setProperty("class", "tde-tray");
}

void
Tray::_init_ui(const DesktopSettings& settings)
{
  auto* layout = new QHBoxLayout{ this };
  setLayout(layout);

  auto* smb = new tray::StartMenuButton{ this };
  layout->addWidget(smb, 0, Qt::AlignVCenter);
  layout->addSpacerItem(
    new QSpacerItem{ 0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum });
  layout->addWidget(
    new tray::Clock{ settings.tray_time_format(), this }, 0, Qt::AlignVCenter);
}

}
