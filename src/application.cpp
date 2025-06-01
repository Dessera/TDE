#include <qapplication.h>
#include <qfile.h>
#include <qlogging.h>

#include "tde/application.hpp"
#include "tde/common.hpp"

namespace tde {

Application::Application(int argc, char** argv)
  : QApplication{ argc, argv }
{
  _init_styles();
  _desktop.show();
}

void
Application::_init_styles()
{
  QFile f{ common::AppStyleSheet };
  if (!f.open(QFile::ReadOnly)) {
    qWarning()
      << "Failed to open application stylesheet, no stylesheet applied";
    return;
  }

  auto style_str = QString::fromUtf8(f.readAll());

  auto url = _settings.desktop_qss();
  if (url.isValid()) {
    QFile f{ url.toLocalFile() };
    if (!f.open(QFile::ReadOnly)) {
      qWarning()
        << "Failed to open user stylesheet, only default stylesheet applied";
    } else {
      style_str += '\n';
      style_str += QString::fromUtf8(f.readAll());
    }
  }

  setStyleSheet(style_str);
}

}
