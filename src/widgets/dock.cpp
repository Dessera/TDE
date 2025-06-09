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
Dock::_create_app(const helpers::AppInfo& app)
{
  auto* app_item = AppItemFactory::create(app, this, Qt::ToolButtonIconOnly);
  connect(
    app_item, &AppItem::request_launch_app, this, &Dock::request_launch_app);

  layout()->addWidget(app_item);
  _dock_apps.append(app_item);
}

void
Dock::_clear_apps()
{
  for (auto* child : _dock_apps) {
    layout()->removeWidget(child);
    child->deleteLater();
  }
  _dock_apps.clear();
}

void
Dock::on_dock_apps_changed(const QList<helpers::AppInfo>& apps)
{
  _clear_apps();

  for (const auto& app : apps) {
    _create_app(app);
  }
}

}
