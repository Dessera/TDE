#pragma once

#include <qcolor.h>
#include <qsettings.h>
#include <qstring.h>
#include <qtclasshelpermacros.h>
#include <qtmetamacros.h>

#define SETTINGS_GETTER(type, name, key)                                       \
  [[nodiscard]] constexpr auto name() const                                    \
  {                                                                            \
    return value(key).value<type>();                                           \
  }

#define SETTINGS_GETTER_DEFAULT(type, name, key, default_value)                \
  [[nodiscard]] constexpr auto name() const                                    \
  {                                                                            \
    return value(key, default_value).value<type>();                            \
  }

namespace tde {

class AppSettings : public QSettings
{
  Q_OBJECT

public:
  AppSettings(const QString& organization,
              const QString& application,
              QObject* parent = nullptr);
  ~AppSettings() override = default;

  Q_DISABLE_COPY(AppSettings)

  SETTINGS_GETTER_DEFAULT(int, desktop_width, "desktop/width", 800)
  SETTINGS_GETTER_DEFAULT(int, desktop_height, "desktop/height", 480)
  SETTINGS_GETTER_DEFAULT(QString, desktop_class, "desktop/class", "tde")
  SETTINGS_GETTER_DEFAULT(QString, desktop_title, "desktop/title", "TDE")
  SETTINGS_GETTER_DEFAULT(QColor,
                          desktop_background_color,
                          "desktop/background_color",
                          QColor(0, 0, 0))
  SETTINGS_GETTER_DEFAULT(QColor, dock_color, "dock/color", QColor(0xFFFFFF))
};

}
