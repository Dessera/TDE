#include <qboxlayout.h>
#include <qdatetime.h>
#include <qlabel.h>
#include <qpushbutton.h>
#include <qtimer.h>
#include <qtoolbutton.h>

#include "tde/widgets/startmenu.hpp"
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
  layout->addWidget(new tray::Clock{ settings.statusbar_time_format(), this },
                    0,
                    Qt::AlignVCenter);

  auto* scrw = new StartMenu{ this };
  connect(smb, &QToolButton::clicked, scrw, [scrw]() { scrw->show(); });
}

}
