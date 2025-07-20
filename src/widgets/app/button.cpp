#include <qsize.h>
#include <qwidget.h>

#include "tde/widgets/app/button.hpp"

namespace tde::widgets::app {

Button::Button(const AppInfo& app, QWidget* parent)
  : QToolButton{ parent }
  , _exec{ app.exec }
{
  setIcon(QIcon{ app.icon });

  setText(app.name);
  setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

  connect(this, &QToolButton::clicked, this, &Button::_on_clicked);
}

Button::AppInfo
Button::to_app_info() const
{
  return { text(), _exec, icon().name() };
}

void
Button::_on_clicked()
{
  emit request_launch_app(to_app_info());
}

}
