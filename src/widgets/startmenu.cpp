#include <qapplication.h>
#include <qboxlayout.h>
#include <qbuttongroup.h>
#include <qevent.h>
#include <qgridlayout.h>
#include <qlabel.h>
#include <qscreen.h>
#include <qtoolbutton.h>
#include <qwidget.h>

#include "tde/widgets/startmenu.hpp"
#include "tde/widgets/startmenu/syspanel.hpp"
#include "tde/widgets/startmenu/toolpanel.hpp"

namespace tde::widgets {

StartMenu::StartMenu(QWidget* parent)
  : QWidget{ parent }
{
  _init();

  auto* layout = new QGridLayout{ this };
  setLayout(layout);

  layout->addWidget(new startmenu::ToolPanel{ this }, 1, 0);
  layout->addWidget(new startmenu::SysPanel{ this }, 0, 1, 2, 1);
}

void
StartMenu::showEvent(QShowEvent* /*event*/)
{
  QScreen* screen = QApplication::primaryScreen();
  if (screen) {
    setGeometry(screen->geometry());
  }
}

void
StartMenu::mousePressEvent(QMouseEvent* event)
{
  if (event->button() == Qt::LeftButton) {
    hide();
  }

  QWidget::mousePressEvent(event);
}

void
StartMenu::keyPressEvent(QKeyEvent* event)
{
  if (event->key() == Qt::Key_Escape) {
    hide();
  }

  QWidget::keyPressEvent(event);
}

void
StartMenu::_init()
{
  setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::Tool);
  setAttribute(Qt::WA_StyledBackground);

  setProperty("class", "tde-startmenu");
}

}
