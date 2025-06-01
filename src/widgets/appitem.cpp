#include <qboxlayout.h>
#include <qlabel.h>
#include <qsize.h>
#include <qwidget.h>

#include "tde/widgets/appitem.hpp"

namespace tde::widgets {

AppItem::AppItem(const QIcon& icon, const QString& name, QWidget* parent)
  : QToolButton{ parent }
{
  setIcon(icon);
  setIconSize(QSize(IconSize, IconSize));

  setText(name);
  setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

  setProperty("class", "tde-app-item");
}

}
