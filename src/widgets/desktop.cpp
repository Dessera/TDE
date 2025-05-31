#include <qboxlayout.h>
#include <qdockwidget.h>
#include <qlabel.h>
#include <qlayoutitem.h>
#include <qpalette.h>
#include <qpushbutton.h>
#include <qtoolbutton.h>
#include <qwidget.h>

#include "tde/widgets/desktop.hpp"
#include "tde/widgets/dock.hpp"

namespace tde {

Desktop::Desktop(const AppSettings& settings, QWidget* parent)
  : QWidget{ parent }
{
  _init(settings);
  _init_ui(settings);
}

void
Desktop::_init(const AppSettings& settings)
{
  auto desktop_cls = settings.desktop_class();
  auto bgcolor = settings.desktop_background_color();

  setWindowTitle(settings.desktop_title());
  resize(settings.desktop_width(), settings.desktop_height());

  setObjectName(desktop_cls);
  setStyleSheet(QString{ "QWidget#%1 { background-color: %2; }" }
                  .arg(desktop_cls)
                  .arg(bgcolor.name()));
}

void
Desktop::_init_ui(const AppSettings& settings)
{
  auto* layout = new QVBoxLayout{ this };
  setLayout(layout);

  layout->addWidget(new QLabel{ "Notify", this });

  layout->addWidget(new QLabel{ "Main", this }, 1);

  layout->addWidget(
    new widgets::Dock{ settings, this }, 0, Qt::AlignHCenter | Qt::AlignBottom);
}

}
