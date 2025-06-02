#pragma once

#include <qcolor.h>
#include <qsettings.h>
#include <qsize.h>
#include <qstring.h>
#include <qtclasshelpermacros.h>
#include <qtmetamacros.h>
#include <qurl.h>

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
  SETTINGS_GETTER_DEFAULT(QString, desktop_title, "desktop/title", "TDE")
  SETTINGS_GETTER_DEFAULT(QSize, desktop_grid, "desktop/grid", QSize(4, 3))
  SETTINGS_GETTER(QString, desktop_qss_path, "desktop/qss_path")
  SETTINGS_GETTER(QString, desktop_app_dir, "desktop/app_dir")
};

}
