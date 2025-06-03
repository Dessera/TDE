#include <qapplication.h>
#include <qfile.h>
#include <qlogging.h>
#include <qobject.h>

#include "tde/application.hpp"
#include "tde/helpers/appfetcher.hpp"
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
  QObject::connect(&_app_fetcher,
                   &helpers::AppFetcher::apps_changed,
                   &_desktop,
                   &widgets::Desktop::apps_changed);

  QObject::connect(&_app_fetcher,
                   &helpers::AppFetcher::dock_apps_changed,
                   &_desktop,
                   &widgets::Desktop::dock_apps_changed);

  QObject::connect(&_desktop,
                   &widgets::Desktop::request_launch_app,
                   &_app_launcher,
                   &helpers::AppLauncher::on_request_launch_app);

  QObject::connect(&_app_launcher,
                   &helpers::AppLauncher::start_app,
                   &_desktop,
                   &widgets::Desktop::on_start_app);

  QObject::connect(&_app_launcher,
                   &helpers::AppLauncher::finish_app,
                   &_desktop,
                   &widgets::Desktop::on_finish_app);

  //  manually fetch apps on startup
  _app_fetcher.refresh();
}

void
Application::_init_styles()
{
  QFile builtin_file{ AppStyleSheet };
  if (!builtin_file.open(QFile::ReadOnly)) {
    qWarning()
      << "Failed to open application stylesheet, no stylesheet applied:"
      << builtin_file.errorString();
    return;
  }
  auto style_str = QString::fromUtf8(builtin_file.readAll());

  qInfo() << "Loaded application stylesheet from:" << AppStyleSheet;

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
