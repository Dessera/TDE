#include "tde/widgets/icon.hpp"

namespace tde::widgets {

QIcon
IconFactory::icon(IconType type)
{
  return QIcon{ ICON_MAP[type] };
}

QIcon
IconFactory::icon(const QString& path)
{
  return QIcon{ path };
}

QPixmap
IconFactory::pixmap(IconType type)
{
  return QPixmap{ ICON_MAP[type] };
}

QPixmap
IconFactory::pixmap(IconType type, const QSize& size)
{
  return QPixmap{ ICON_MAP[type] }.scaled(size);
}

QPixmap
IconFactory::pixmap(const QString& path)
{
  return QPixmap{ path };
}

}
