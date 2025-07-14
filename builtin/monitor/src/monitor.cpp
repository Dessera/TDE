#include <tde/sys/cpu.hpp>

#include "monitor.hpp"
#include "qboxlayout.h"
#include "qlabel.h"
#include "tde/widgets/ringprogress.hpp"

Monitor::Monitor(const tde::DesktopSettings& /*settings*/, QWidget* parent)
  : QWidget{ parent }
  , _tim{ new QTimer{ this } }
  , _ring{ new tde::widgets::RingProgress{ this } }
{
  connect(_tim, &QTimer::timeout, this, &Monitor::_on_timeout);
  _tim->start(1000);

  auto* layout = new QVBoxLayout{ this };
  setLayout(layout);

  _ring->setMinimumSize(200, 200);
  _ring->set_text("CPU Usage");
  layout->addWidget(_ring);

  auto info = tde::sys::query_cpu_info();
  layout->addWidget(new QLabel{ tde::sys::get_cpu_info_summary(info), this });
}

void
Monitor::_on_timeout()
{
  using namespace tde::sys;

  static auto prev_status = CPUStatus{};

  auto current = query_cpu_status();
  auto usage = get_cpu_usage(prev_status, current);

  qDebug() << "CPU Usage: " << usage;

  _ring->set_value(static_cast<int>(usage * 100.0));
  _ring->set_text(
    QString{ "CPU Usage: %1%" }.arg(static_cast<int>(usage * 100.0)));

  prev_status = current;
}
