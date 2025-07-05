#include <qicon.h>
#include <qsize.h>
#include <qwidget.h>

#include "tde/widgets/appitem.hpp"

namespace tde::widgets {

AppItem::AppItem(const app::Info& app, QWidget* parent)
  : QToolButton{ parent }
  , _exec(app.exec)
{
  setIcon(QIcon{ app.icon });
  setIconSize(QSize(ICON_SIZE, ICON_SIZE));

  setText(app.name);
  setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

  setProperty("class", "tde-app-item");

  connect(this, &QToolButton::released, this, &AppItem::_on_released);
}

app::Info
AppItem::to_app_info() const
{
  return { text(), _exec, icon().name() };
}

void
AppItem::_on_released()
{
  auto app_info = to_app_info();

  qInfo() << "Request launch app:" << app_info.name;

  emit request_launch_app(app_info);
}

}
