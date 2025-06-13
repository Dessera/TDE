#include <qboxlayout.h>
#include <qwidget.h>

#include "tde/widgets/appitem.hpp"
#include "tde/widgets/dock.hpp"

namespace tde::widgets {

Dock::Dock(QWidget* parent)
  : QWidget{ parent }
{
  _init();
  _init_ui();
}

void
Dock::_init()
{
  setAttribute(Qt::WA_StyledBackground);
  setProperty("class", "tde-dock");
}

void
Dock::_init_ui()
{
  auto* layout = new QHBoxLayout(this);
  setLayout(layout);
}

void
Dock::_create_app(const app::Info& app)
{
  auto* app_item = new AppItem{ app, this };
  app_item->setToolButtonStyle(Qt::ToolButtonIconOnly);

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
Dock::on_dock_apps_changed(const QList<app::Info>& apps)
{
  _clear_apps();

  for (const auto& app : apps) {
    _create_app(app);
  }
}

}
