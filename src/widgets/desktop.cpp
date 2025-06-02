#include <qboxlayout.h>
#include <qdockwidget.h>
#include <qlabel.h>
#include <qlayoutitem.h>
#include <qpalette.h>
#include <qtoolbutton.h>
#include <qwidget.h>

#include "tde/widgets/applist.hpp"
#include "tde/widgets/desktop.hpp"
#include "tde/widgets/dock.hpp"

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

  auto* label = new QLabel{ "Notify", this };
  label->setProperty("class", "tde-statusbar");
  layout->addWidget(label);

  auto* app_list = new AppList{ settings, this };
  layout->addWidget(app_list, 1);

  layout->addWidget(
    new widgets::Dock{ settings, this }, 0, Qt::AlignHCenter | Qt::AlignBottom);

  connect(this, &Desktop::apps_changed, app_list, &AppList::on_apps_changed);
}

}
