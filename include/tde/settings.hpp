/**
 * @file settings.hpp
 * @author Dessera (dessera@qq.com)
 * @brief Desktop settings.
 * @version 0.1.0
 * @date 2025-06-02
 *
 * @copyright Copyright (c) 2025 Dessera
 *
 */

#pragma once

#include <qsettings.h>
#include <qstring.h>

#include "tde/common.hpp"

namespace tde {

/**
 * @brief Desktop settings.
 *
 */
class TDE_PUBLIC DesktopSettings : public QSettings
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
                  QObject* parent = nullptr)
    : QSettings{ QSettings::IniFormat,
                 QSettings::UserScope,
                 organization,
                 application,
                 parent }
  {
  }

  ~DesktopSettings() override = default;

  Q_DISABLE_COPY(DesktopSettings)

  /**
   * @brief Get the desktop width.
   *
   * @return int Desktop width.
   */
  [[nodiscard]] TDE_INLINE auto desktop_width() const
  {
    return value("desktop/width", 800).value<int>(); // NOLINT
  }

  /**
   * @brief Get the desktop height.
   *
   * @return int Desktop height.
   */
  [[nodiscard]] TDE_INLINE auto desktop_height() const
  {
    return value("desktop/height", 480).value<int>(); // NOLINT
  }

  /**
   * @brief Get the desktop title.
   *
   * @return QString Desktop title.
   */
  [[nodiscard]] TDE_INLINE auto desktop_title() const
  {
    return value("desktop/title", "TDE").value<QString>();
  }

  /**
   * @brief Get the desktop grid x size.
   *
   * @return int Desktop grid x size.
   */
  [[nodiscard]] TDE_INLINE auto desktop_grid_x() const
  {
    return value("desktop/grid_x", 4).value<int>();
  }

  /**
   * @brief Get the desktop grid y size.
   *
   * @return int Desktop grid y size.
   */
  [[nodiscard]] TDE_INLINE auto desktop_grid_y() const
  {
    return value("desktop/grid_y", 3).value<int>();
  }

  /**
   * @brief Get the desktop qss path.
   *
   * @return QString Desktop qss path.
   */
  [[nodiscard]] TDE_INLINE auto desktop_qss_path() const
  {
    return value("desktop/qss_path").value<QString>();
  }

  /**
   * @brief Get the desktop apps.json path.
   *
   * @return QString Desktop apps.json path.
   */
  [[nodiscard]] TDE_INLINE auto desktop_app_path() const
  {
    return value("desktop/app_path").value<QString>();
  }

  /**
   * @brief Get the tray time format.
   *
   * @return QString tray time format.
   */
  [[nodiscard]] TDE_INLINE auto tray_time_format() const
  {
    return value("tray/time_format", "yyyy/MM/dd | hh:mm:ss").value<QString>();
  }
};

}
