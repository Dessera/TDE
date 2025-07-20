#pragma once

#include <cstdint>
#include <qicon.h>
#include <qpixmap.h>

#include "tde/common.hpp"

namespace tde::assets {

class TDE_PUBLIC Icons
{
public:
  enum class Type : uint8_t
  {
    DEFAULT,
    FOLDER_BUILD,
    HELP_ABOUT,
    OFFICE_CHART_PIE,
    WINDOW_CLOSE,
  };

  static QIcon icon(Type type);
  static QIcon icon(const QString& name);

  static QPixmap pixmap(Type type);
  static QPixmap pixmap(const QString& name);
};

}
