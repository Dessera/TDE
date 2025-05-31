#include <qboxlayout.h>
#include <qicon.h>
#include <qlabel.h>
#include <qpainter.h>
#include <qpalette.h>
#include <qstyleoption.h>
#include <qtoolbutton.h>
#include <qwidget.h>

#include "tde/widgets/desktopitem.hpp"
#include "tde/widgets/dock.hpp"

namespace tde::widgets {

Dock::Dock(const AppSettings& settings, QWidget* parent)
  : QWidget{ parent }
{
  _init(settings);
  _init_ui(settings);
}

void
Dock::_init(const AppSettings& settings)
{
  auto bgcolor = settings.dock_color();

  setAttribute(Qt::WA_StyledBackground);
  setStyleSheet(
    QString{ "QWidget { background-color: %1; }" }.arg(bgcolor.name()));
}

void
Dock::_init_ui(const AppSettings& /*settings*/)
{
  auto* layout = new QHBoxLayout(this);
  setLayout(layout);

  layout->addWidget(
    new DesktopItem{ QIcon(":/icons/default-icon.svg"), "app1", this });

  layout->addWidget(
    new DesktopItem{ QIcon(":/icons/default-icon.svg"), "app2", this });

  layout->addWidget(
    new DesktopItem{ QIcon(":/icons/default-icon.svg"), "app3", this });
}

}
