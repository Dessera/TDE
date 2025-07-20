#pragma once

#include <cstdint>
#include <qicon.h>
#include <qpixmap.h>

#include "tde/common.hpp"

namespace tde::assets::icons {

enum class Type : uint8_t
{
  DEFAULT,
  FOLDER_BUILD,
  HELP_ABOUT,
  OFFICE_CHART_PIE,
  WINDOW_CLOSE,
};

TDE_PUBLIC QIcon
icon(Type type);

TDE_PUBLIC QIcon
icon(const QString& name);

TDE_PUBLIC QPixmap
pixmap(Type type);

TDE_PUBLIC QPixmap
pixmap(const QString& name);

}
