#include <qicon.h>
#include <qmap.h>
#include <qpixmap.h>
#include <qstring.h>

#include "tde/assets/icons.hpp"
#include "tde/common.hpp"

namespace tde::assets::icons {

namespace {

const QMap<Type, QString> ICONS_MAP = {
  { Type::DEFAULT, ":/tde/icons/default.svg" },
  { Type::FOLDER_BUILD, ":/tde/icons/folder-build.svg" },
  { Type::HELP_ABOUT, ":/tde/icons/help-about.svg" },
  { Type::OFFICE_CHART_PIE, ":/tde/icons/office-chart-pie.svg" },
  { Type::WINDOW_CLOSE, ":/tde/icons/window-close.svg" },
};

TDE_INLINE QString
_icon_type_to_path(Type type)
{
  return ICONS_MAP[type];
}

}

QIcon
icon(Type type)
{
  return icon(_icon_type_to_path(type));
}

QIcon
icon(const QString& name)
{
  return QIcon{ name };
}

QPixmap
pixmap(Type type)
{
  return pixmap(_icon_type_to_path(type));
}

QPixmap
pixmap(const QString& name)
{
  return QPixmap{ name };
}

}
