#include <qboxlayout.h>
#include <qwidget.h>

#include "tde/widgets/applist.hpp"
#include "tde/widgets/desktop.hpp"
#include "tde/widgets/dock.hpp"
#include "tde/widgets/tray.hpp"

namespace tde::widgets {

Desktop::Desktop(const DesktopSettings& settings, QWidget* parent)
  : QWidget{ parent }
{
  _init(settings);
  _init_ui(settings);
}

void
Desktop::_init(const DesktopSettings& settings)
{
  setWindowTitle(settings.desktop_title());
  resize(settings.desktop_width(), settings.desktop_height());

  setProperty("class", "tde-desktop");
}

void
Desktop::_init_ui(const DesktopSettings& settings)
{
  auto* layout = new QVBoxLayout{ this };
  layout->setContentsMargins(0, 0, 0, DockMargin);
  setLayout(layout);

  layout->addWidget(new Tray{ settings, this });

  auto* app_list = new AppList{ settings, this };
  layout->addWidget(app_list, 1);

  connect(this, &Desktop::apps_changed, app_list, &AppList::on_apps_changed);
  connect(
    app_list, &AppList::request_launch_app, this, &Desktop::request_launch_app);

  auto* dock = new Dock{ this };
  layout->addWidget(dock, 0, Qt::AlignHCenter | Qt::AlignBottom);

  connect(this, &Desktop::dock_apps_changed, dock, &Dock::on_dock_apps_changed);
  connect(dock, &Dock::request_launch_app, this, &Desktop::request_launch_app);
}

void
Desktop::on_start_app(const app::Info& /*app*/)
{
  this->hide();
}

void
Desktop::on_finish_app(int /*code*/, QProcess::ExitStatus /*status*/)
{
  this->show();
}

}
