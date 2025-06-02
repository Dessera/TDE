/**
 * @file settings.hpp
 * @author Dessera (dessera@qq.com)
 * @brief Desktop settings
 * @version 0.1.0
 * @date 2025-06-02
 *
 * @copyright Copyright (c) 2025 Dessera
 *
 */

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

/**
 * @brief Desktop settings.
 *
 */
class DesktopSettings : public QSettings
{
  Q_OBJECT

public:
  /**
   * @brief Construct a new Desktop Settings object.
   *
   * @param organization Application organization.
   * @param application Application name.
   * @param parent Parent object.
   */
  DesktopSettings(const QString& organization,
                  const QString& application,
                  QObject* parent = nullptr);
  ~DesktopSettings() override = default;

  Q_DISABLE_COPY(DesktopSettings)

  SETTINGS_GETTER_DEFAULT(int, desktop_width, "desktop/width", 800)
  SETTINGS_GETTER_DEFAULT(int, desktop_height, "desktop/height", 480)
  SETTINGS_GETTER_DEFAULT(QString, desktop_title, "desktop/title", "TDE")
  SETTINGS_GETTER_DEFAULT(int, desktop_grid_x, "desktop/grid_x", 4)
  SETTINGS_GETTER_DEFAULT(int, desktop_grid_y, "desktop/grid_y", 3)
  SETTINGS_GETTER(QString, desktop_qss_path, "desktop/qss_path")
  SETTINGS_GETTER(QString, desktop_app_path, "desktop/app_path")
};

}
