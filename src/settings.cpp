#include "tde/settings.hpp"

namespace tde {

DesktopSettings::DesktopSettings(const QString& organization,
                                 const QString& application,
                                 QObject* parent)
  : QSettings{ QSettings::IniFormat,
               QSettings::UserScope,
               organization,
               application,
               parent }
{
}

}
