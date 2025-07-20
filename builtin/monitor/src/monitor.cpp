#include <qboxlayout.h>
#include <resource_monitor.hpp>
#include <tde/assets/icons.hpp>
#include <tde/sys/cpu.hpp>
#include <tde/widgets/router.hpp>

#include "monitor.hpp"

Monitor::Monitor(const tde::DesktopSettings& /*settings*/, QWidget* parent)
  : QWidget{ parent }
{
  using tde::assets::Icons;

  auto* layout = new QVBoxLayout{ this };
  layout->setContentsMargins(0, 0, 0, 0);
  setLayout(layout);

  auto* router = new tde::widgets::Router{ this };
  router->add({ "Resources", Icons::icon(Icons::Type::OFFICE_CHART_PIE) },
              new ResourceMonitor{ this });

  layout->addWidget(router);
}
