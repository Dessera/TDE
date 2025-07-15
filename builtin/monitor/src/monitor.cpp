#include <tde/sys/cpu.hpp>

#include "monitor.hpp"
#include "qboxlayout.h"
#include "qlabel.h"
#include "tde/widgets/icon.hpp"
#include "tde/widgets/router.hpp"

Monitor::Monitor(const tde::DesktopSettings& /*settings*/, QWidget* parent)
  : QWidget{ parent }
  , _tim{ new QTimer{ this } }
{
  setProperty("class", "tde-application");

  auto* layout = new QVBoxLayout{ this };
  layout->setContentsMargins(0, 0, 0, 0);
  setLayout(layout);

  auto* router = new tde::widgets::Router{ this };
  router->add(
    { "Item1",
      tde::widgets::IconFactory::icon(tde::widgets::IconType::HELP_ABOUT) },
    new QLabel{ "Item1", this });

  router->add(
    { "Item2",
      tde::widgets::IconFactory::icon(tde::widgets::IconType::HELP_ABOUT) },
    new QLabel{ "Item2", this });

  router->remove("Item1");

  layout->addWidget(router);

  // connect(_tim, &QTimer::timeout, this, &Monitor::_on_timeout);
  // _tim->start(1000);

  // auto* layout = new QVBoxLayout{ this };
  // setLayout(layout);

  // _ring->setMinimumSize(200, 200);
  // _ring->set_text("CPU Usage");
  // layout->addWidget(_ring);

  // auto info = tde::sys::query_cpu_info();
  // layout->addWidget(new QLabel{ tde::sys::get_cpu_info_summary(info), this
  // });
}

void
Monitor::_on_timeout()
{
  using namespace tde::sys;

  static auto prev_status = CPUStatus{};

  auto current = query_cpu_status();
  auto usage = get_cpu_usage(prev_status, current);

  qDebug() << "CPU Usage: " << usage;

  prev_status = current;
}
