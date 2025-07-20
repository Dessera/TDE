#include <qboxlayout.h>
#include <qtoolbutton.h>

#include "tde/widgets/tray.hpp"
#include "tde/widgets/tray/clock.hpp"

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
}

void
Tray::_init_ui(const DesktopSettings& settings)
{
  auto* layout = new QHBoxLayout{ this };
  setLayout(layout);

  layout->addWidget(
    new tray::Clock{ settings.tray_time_format(), this }, 0, Qt::AlignCenter);
}

}
