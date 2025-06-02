#include <qboxlayout.h>
#include <qicon.h>
#include <qlabel.h>
#include <qpainter.h>
#include <qpalette.h>
#include <qstyleoption.h>
#include <qtoolbutton.h>
#include <qwidget.h>

#include "tde/widgets/appitem.hpp"
#include "tde/widgets/dock.hpp"

namespace tde::widgets {

Dock::Dock(const DesktopSettings& settings, QWidget* parent)
  : QWidget{ parent }
{
  _init(settings);
  _init_ui(settings);
}

void
Dock::_init(const DesktopSettings& /*settings*/)
{
  setAttribute(Qt::WA_StyledBackground);
  setProperty("class", "tde-dock");
}

void
Dock::_init_ui(const DesktopSettings& /*settings*/)
{
  auto* layout = new QHBoxLayout(this);
  setLayout(layout);

  layout->addWidget(
    new AppItem{ QIcon(":/icons/default-icon.svg"), "app1", this });

  layout->addWidget(
    new AppItem{ QIcon(":/icons/default-icon.svg"), "app2", this });

  layout->addWidget(
    new AppItem{ QIcon(":/icons/default-icon.svg"), "app3", this });
}

}
