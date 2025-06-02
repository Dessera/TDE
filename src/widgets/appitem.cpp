#include <qboxlayout.h>
#include <qicon.h>
#include <qlabel.h>
#include <qsize.h>
#include <qwidget.h>

#include "qtoolbutton.h"
#include "tde/helpers/appfetcher.hpp"
#include "tde/widgets/appitem.hpp"

namespace tde::widgets {

AppItem::AppItem(const helpers::AppInfo& app, QWidget* parent)
  : QToolButton{ parent }
  , _exec(app.exec)
{
  setIcon(QIcon{ app.icon });
  setIconSize(QSize(IconSize, IconSize));

  setText(app.name);
  setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

  setProperty("class", "tde-app-item");

  connect(this, &QToolButton::released, this, &AppItem::on_released);
}

void
AppItem::on_released()
{
  auto app_info = AppItemFactory::create_app_info(this);

  qInfo() << "Request launch app:" << app_info.name;

  emit request_launch_app(app_info);
}

AppItem*
AppItemFactory::create(const helpers::AppInfo& app,
                       QWidget* parent,
                       bool show_text)
{
  auto* app_item = new AppItem(app, parent);
  if (!show_text) {
    app_item->setToolButtonStyle(Qt::ToolButtonIconOnly);
  }
  return app_item;
}

helpers::AppInfo
AppItemFactory::create_app_info(const AppItem* item)
{
  return helpers::AppInfo{
    .name = item->text(),
    .exec = item->exec(),
    .icon = item->icon().name(),
  };
}

}
