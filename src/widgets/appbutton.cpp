#include <qsize.h>
#include <qwidget.h>

#include "tde/config.hpp"
#include "tde/widgets/appbutton.hpp"
#include "tde/widgets/icon.hpp"

namespace tde::widgets {

AppButton::AppButton(const app::Info& app, QWidget* parent)
  : QToolButton{ parent }
  , _exec{ app.exec }
{
  setIcon(IconFactory::icon(app.icon));
  setIconSize(QSize{ config::APP_ICON_SIZE, config::APP_ICON_SIZE });

  setText(app.name);
  setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

  setProperty("class", "tde-app-button");

  connect(this, &QToolButton::clicked, this, &AppButton::_on_clicked);
}

app::Info
AppButton::to_app_info() const
{
  return { text(), _exec, icon().name() };
}

void
AppButton::_on_clicked()
{
  auto app_info = to_app_info();

  qInfo() << "Request launch app:" << app_info.name;
  emit request_launch_app(app_info);
}

}
