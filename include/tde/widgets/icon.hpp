/**
 * @file icon.hpp
 * @author Dessera (dessera@qq.com)
 * @brief Icon factory.
 * @version 0.1.0
 * @date 2025-07-07
 *
 * @copyright Copyright (c) 2025 Dessera
 *
 */

#pragma once

#include <cstdint>
#include <qicon.h>
#include <qmap.h>
#include <qpixmap.h>

#include "tde/common.hpp"

namespace tde::widgets {

/**
 * @brief Embedded icon type.
 *
 */
enum class IconType : uint8_t
{
  DEFAULT,
  HELP_ABOUT,
  WINDOW_CLOSE,
};

/**
 * @brief Icon factory to load icons.
 *
 */
class TDE_PUBLIC IconFactory
{
public:
  inline static const QMap<IconType, QString> ICON_MAP = {
    { IconType::DEFAULT, ":/tde/icons/default.svg" },
    { IconType::HELP_ABOUT, ":/tde/icons/help-about.svg" },
    { IconType::WINDOW_CLOSE, ":/tde/icons/window-close.svg" },
  }; /**< Icon map. */

  /**
   * @brief Get icon from type.
   *
   * @param type Icon type.
   * @return QIcon Icon.
   */
  static QIcon icon(IconType type);

  /**
   * @brief Get icon from path.
   *
   * @param path Icon path.
   * @return QIcon Icon.
   */
  static QIcon icon(const QString& path);

  /**
   * @brief Get pixmap from type.
   *
   * @param type Icon type.
   * @return QPixmap Pixmap.
   */
  static QPixmap pixmap(IconType type);

  /**
   * @brief Get pixmap from type and size.
   *
   * @param type Icon type.
   * @param size Icon size.
   * @return QPixmap Pixmap.
   */
  static QPixmap pixmap(IconType type, const QSize& size);

  /**
   * @brief Get pixmap from path.
   *
   * @param path Icon path.
   * @return QPixmap Pixmap.
   */
  static QPixmap pixmap(const QString& path);
};

}
