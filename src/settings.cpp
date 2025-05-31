#include "tde/settings.hpp"

namespace tde {

AppSettings::AppSettings(const QString& organization,
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
