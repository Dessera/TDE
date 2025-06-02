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
}

void
Dock::on_dock_apps_changed(const QList<helpers::AppInfo>& apps)
{
  for (auto* child : findChildren<AppItem*>()) {
    layout()->removeWidget(child);
    child->deleteLater();
  }

  for (const auto& app : apps) {
    auto* app_item = new AppItem{ QIcon{ app.icon }, app.name, this };
    app_item->setToolButtonStyle(Qt::ToolButtonIconOnly);
    layout()->addWidget(app_item);
  }
}

}
