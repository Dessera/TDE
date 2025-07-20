#include <qicon.h>
#include <qmap.h>
#include <qpixmap.h>
#include <qstring.h>

#include "tde/assets/icons.hpp"
#include "tde/common.hpp"

namespace {

class IconsHelper
{
private:
  using IconType = tde::assets::Icons::Type;

  inline static const QMap<IconType, QString> ICONS_MAP = {
    { IconType::DEFAULT, ":/tde/icons/default.svg" },
    { IconType::FOLDER_BUILD, ":/tde/icons/folder-build.svg" },
    { IconType::HELP_ABOUT, ":/tde/icons/help-about.svg" },
    { IconType::OFFICE_CHART_PIE, ":/tde/icons/office-chart-pie.svg" },
    { IconType::WINDOW_CLOSE, ":/tde/icons/window-close.svg" },
  };

public:
  static TDE_INLINE QString icon_type_to_path(IconType type)
  {
    return ICONS_MAP[type];
  }
};

}

namespace tde::assets {

QIcon
Icons::icon(Type type)
{
  return icon(IconsHelper::icon_type_to_path(type));
}

QIcon
Icons::icon(const QString& name)
{
  return QIcon{ name };
}

QPixmap
Icons::pixmap(Type type)
{
  return pixmap(IconsHelper::icon_type_to_path(type));
}

QPixmap
Icons::pixmap(const QString& name)
{
  return QPixmap{ name };
}

}
