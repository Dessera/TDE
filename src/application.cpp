#include <qapplication.h>
#include <qfile.h>
#include <qlogging.h>
#include <qobject.h>

#include "tde/application.hpp"
#include "tde/widgets/desktop.hpp"

namespace tde {

Application::Application(int argc, char** argv)
  : QApplication{ argc, argv }
{
  _init_styles();
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

void
Application::_init_styles()
{
  auto builtin_file = QFile{ config::APP_STYLESHEET };
  if (!builtin_file.open(QFile::ReadOnly)) {
    qWarning()
      << "Failed to open application stylesheet, no stylesheet applied:"
      << builtin_file.errorString();
    return;
  }
  auto style_str = QString::fromUtf8(builtin_file.readAll());

  qInfo() << "Loaded application stylesheet from:" << config::APP_STYLESHEET;

  auto file = QFile{ _settings.desktop_qss_path() };
  if (file.exists()) {
    if (!file.open(QFile::ReadOnly)) {
      qWarning()
        << "Failed to open user stylesheet, only default stylesheet applied:"
        << file.errorString();
    } else {
      style_str += '\n';
      style_str += QString::fromUtf8(file.readAll());
    }

    qInfo() << "Loaded user stylesheet from:" << _settings.desktop_qss_path();
  }

  setStyleSheet(style_str);
}

}
