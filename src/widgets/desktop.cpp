#include <qboxlayout.h>
#include <qwidget.h>

#include "tde/widgets/app/card.hpp"
#include "tde/widgets/desktop.hpp"
#include "tde/widgets/dock.hpp"
#include "tde/widgets/tray.hpp"

namespace tde::widgets {

Desktop::Desktop(const DesktopSettings& settings, QWidget* parent)
  : QWidget{ parent }
  , _app_fetcher{ settings.desktop_app_path() }
{
  _init(settings);
  _init_ui(settings);

  _app_fetcher.refresh();
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
  layout->setContentsMargins(0, 0, 0, DOCK_MARGIN);
  setLayout(layout);

  layout->addWidget(new Tray{ settings, this });

  auto* app_list = new app::CardList{
    QSize{ settings.desktop_grid_x(), settings.desktop_grid_y() }, this
  };
  layout->addWidget(app_list, 1);

  connect(&_app_fetcher,
          &AppFetcher::apps_changed,
          app_list,
          &app::CardList::on_apps_changed);
  connect(app_list,
          &app::CardList::request_launch_app,
          &_app_launcher,
          &AppLauncher::on_request_launch_app);

  auto* dock = new Dock{ this };
  layout->addWidget(dock, 0, Qt::AlignHCenter | Qt::AlignBottom);

  connect(&_app_fetcher,
          &AppFetcher::dock_apps_changed,
          dock,
          &Dock::on_dock_apps_changed);
  connect(dock,
          &Dock::request_launch_app,
          &_app_launcher,
          &AppLauncher::on_request_launch_app);
}

}
