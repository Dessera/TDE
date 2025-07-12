#include <tde/sys/cpu.hpp>

#include "monitor.hpp"

Monitor::Monitor(const tde::DesktopSettings& /*settings*/, QWidget* parent)
  : QWidget{ parent }
  , _tim{ new QTimer{ this } }
{
  connect(_tim, &QTimer::timeout, this, &Monitor::_on_timeout);
  _tim->start(1000);
}

void
Monitor::_on_timeout()
{
  using namespace tde::sys;

  auto res = query_cpu_info();

  qDebug() << "System:" << res.system;
  qDebug() << "User:" << res.user;
}
