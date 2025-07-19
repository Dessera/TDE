#include <qboxlayout.h>
#include <qlabel.h>
#include <tde/sys/cpu.hpp>
#include <tde/sys/memory.hpp>
#include <tde/widgets/text/header.hpp>

#include "resource_monitor.hpp"

ResourceUsageMonitor::ResourceUsageMonitor(QWidget* parent)
  : QWidget{ parent }
  , _tim{ new QTimer{ this } }
  , _cpu{ new tde::widgets::RingProgress{ this } }
  , _mem{ new tde::widgets::RingProgress{ this } }
  , _swap{ new tde::widgets::RingProgress{ this } }
  , _cpu_prev{}
{
  auto* layout = new QHBoxLayout{ this };
  setLayout(layout);

  layout->addWidget(_cpu);
  layout->addWidget(_mem);
  layout->addWidget(_swap);

  _tim->setInterval(REFRESH_INTERVAL);
  connect(
    _tim, &QTimer::timeout, this, &ResourceUsageMonitor::_on_timer_timeout);
  _tim->start();

  refresh();
}

void
ResourceUsageMonitor::refresh()
{
  using namespace tde::sys;

  auto cpu_curr = query_cpu_status();
  auto cpu_usage = get_cpu_usage(_cpu_prev, cpu_curr) * 100.0;
  _cpu_prev = cpu_curr;

  _cpu->set_value(static_cast<int>(cpu_usage));
  _cpu->set_text(QString{ "CPU Usage: %1%" }.arg(cpu_usage, 0, 'f', 2));

  auto mem_curr = query_memory_status();
  auto mem_usage = static_cast<double>(mem_curr.total - mem_curr.free) /
                   static_cast<double>(mem_curr.total) * 100.0;

  _mem->set_value(static_cast<int>(mem_usage));
  _mem->set_text(QString{ "Mem Usage: %1%" }.arg(mem_usage, 0, 'f', 2));

  auto swap_usage =
    static_cast<double>(mem_curr.swap_total - mem_curr.swap_free) /
    static_cast<double>(mem_curr.swap_total) * 100.0;

  _swap->set_value(static_cast<int>(swap_usage));
  _swap->set_text(QString{ "Swap Usage: %1%" }.arg(swap_usage, 0, 'f', 2));
}

void
ResourceUsageMonitor::_on_timer_timeout()
{
  refresh();
}

ResourceMonitor::ResourceMonitor(QWidget* parent)
  : QWidget{ parent }
{
  auto* layout = new QVBoxLayout{ this };
  setLayout(layout);

  layout->addWidget(new ResourceUsageMonitor{ this }, 1);

  _create_cpu_info();
  _create_mem_info();
}

void
ResourceMonitor::_create_cpu_info()
{
  using namespace tde::sys;
  using namespace tde::widgets::text;

  auto* _layout = qobject_cast<QVBoxLayout*>(layout());

  auto cpus = query_cpu_info();
  auto cpu_summary = get_cpu_info_summary(cpus);

  _layout->addWidget(new H4{ "CPUs:", this });
  _layout->addWidget(new QLabel{ cpu_summary, this });
}

void
ResourceMonitor::_create_mem_info()
{
  using namespace tde::sys;
  using namespace tde::widgets::text;

  auto* _layout = qobject_cast<QVBoxLayout*>(layout());

  auto mem_info = query_memory_status();

  _layout->addWidget(new H4{ "Memory:", this });
  _layout->addWidget(
    new QLabel{ QString{ "Physical / Swap: %1 GB / %2 GB" }
                  .arg(bytes_to_gb(mem_info.total), 0, 'f', 2)
                  .arg(bytes_to_gb(mem_info.swap_total), 0, 'f', 2),
                this });
}
