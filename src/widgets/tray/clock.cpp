#include <qdatetime.h>
#include <qtimer.h>

#include "tde/widgets/tray/clock.hpp"

namespace tde::widgets::tray {

Clock::Clock(QString format, QWidget* parent)
  : QLabel{ parent }
  , _format(std::move(format))
  , _timer{ new QTimer{ this } }
{
  connect(_timer, &QTimer::timeout, this, &Clock::_on_timeout);
  _timer->start(TIME_UPDATE_INTERVAL);

  _on_timeout();
}

void
Clock::_on_timeout()
{
  setText(QDateTime::currentDateTime().toString(_format));
}

}
