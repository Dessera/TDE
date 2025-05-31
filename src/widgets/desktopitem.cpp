#include <qboxlayout.h>
#include <qlabel.h>
#include <qsize.h>
#include <qwidget.h>

#include "tde/widgets/desktopitem.hpp"

namespace tde::widgets {

DesktopItem::DesktopItem(const QIcon& icon,
                         const QString& name,
                         QWidget* parent)
  : QToolButton{ parent }
{
  setIcon(icon);
  setIconSize(QSize(IconSize, IconSize));

  setText(name);
  setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

  setStyleSheet("QToolButton {"
                "padding: 0px;"
                "border-style: flat;"
                "background: transparent;"
                "}");
}

}
