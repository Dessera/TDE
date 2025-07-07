#include <qapplication.h>
#include <qfile.h>
#include <qlogging.h>
#include <qobject.h>

#include "tde/application.hpp"
#include "tde/widgets/desktop.hpp"
#include "tde/widgets/style.hpp"

namespace tde {

Application::Application(int argc, char** argv)
  : QApplication{ argc, argv }
{
  setStyleSheet(widgets::StyleFactory::generate_qss(_settings));

  _init();
  _desktop.show();
}

void
Application::_init()
{
  connect(&_app_fetcher,
          &app::Fetcher::apps_changed,
          &_desktop,
          &widgets::Desktop::apps_changed);

  connect(&_app_fetcher,
          &app::Fetcher::dock_apps_changed,
          &_desktop,
          &widgets::Desktop::dock_apps_changed);

  connect(&_desktop,
          &widgets::Desktop::request_launch_app,
          &_app_launcher,
          &app::Launcher::on_request_launch_app);

  connect(&_app_launcher,
          &app::Launcher::before_app_start,
          &_desktop,
          &widgets::Desktop::on_app_start);

  connect(&_app_launcher,
          &app::Launcher::after_app_finish,
          &_desktop,
          &widgets::Desktop::on_app_finish);

  // manually fetch apps on startup
  _app_fetcher.refresh();
}

}
