#include <qboxlayout.h>
#include <qdatetime.h>
#include <qlabel.h>
#include <qpushbutton.h>
#include <qtimer.h>
#include <qtoolbutton.h>

#include "tde/widgets/statusbar.hpp"

namespace tde::widgets {

StatusBar::StatusBar(const DesktopSettings& settings, QWidget* parent)
  : QWidget{ parent }
{
  _init(settings);
  _init_ui(settings);
}

void
StatusBar::_init(const DesktopSettings& /*settings*/)
{
  setAttribute(Qt::WA_StyledBackground);
  setProperty("class", "tde-statusbar");
}

void
StatusBar::_init_ui(const DesktopSettings& settings)
{
  auto* layout = new QHBoxLayout{ this };
  setLayout(layout);

  layout->addWidget(new StartMenuButton{ this }, 0, Qt::AlignVCenter);
  layout->addSpacerItem(
    new QSpacerItem{ 0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum });
  layout->addWidget(new TimeLabel{ settings.statusbar_time_format(), this },
                    0,
                    Qt::AlignVCenter);
}

StartMenuButton::StartMenuButton(QWidget* parent)
  : QToolButton{ parent }
{
  setProperty("class", "tde-start-menu-button");
  setText("Start");
  setIcon(QIcon{ StartMenuIcon });
  setIconSize({ StartMenuIconSize, StartMenuIconSize });
}

TimeLabel::TimeLabel(QString format, QWidget* parent)
  : QLabel{ parent }
  , _format(std::move(format))
  , _timer{ new QTimer{ this } }
{
  setProperty("class", "tde-time-label");

  connect(_timer, &QTimer::timeout, this, &TimeLabel::_on_timeout);
  _timer->start(TimeUpdateInterval);

  _on_timeout();
}

void
TimeLabel::_on_timeout()
{
  setText(QDateTime::currentDateTime().toString(_format));
}

}
