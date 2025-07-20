/**
 * @file styles.hpp
 * @author Dessera (dessera@qq.com)
 * @brief Styles utils.
 * @version 0.1.0
 * @date 2025-07-18
 *
 * @copyright Copyright (c) 2025 Dessera
 *
 */

#pragma once

#include <cstdint>
#include <qstring.h>
#include <qstringlist.h>

#include "tde/common.hpp"

namespace tde::assets::styles {

/**
 * @brief Scope of style sheet.
 *
 */
enum class Scope : uint8_t
{
  DESKTOP = 0b001,     /**< Styles for desktop components. */
  APPLICATION = 0b010, /**< Styles for application components. */
  COMPONENTS = 0b100,  /**< Styles for common components. */
  ALL = DESKTOP | APPLICATION | COMPONENTS /**< All styles. */
};

/**
 * @brief Generate qss with builtin scope.
 *
 * @param scope Builtin scope.
 * @return QString Qss content.
 */
TDE_PUBLIC QString
generate(Scope scope);

/**
 * @brief Generate qss with files list.
 *
 * @param files Files list.
 * @return QString Qss content.
 */
TDE_PUBLIC QString
generate(const QStringList& files);

/**
 * @brief Generate qss with builtin scope and extra files list.
 *
 * @param scope Builtin scope.
 * @param files Files list.
 * @return QString Qss content.
 */
TDE_PUBLIC QString
generate(Scope scope, const QStringList& files);

/**
 * @brief Generate qss with builtin scope and extra files (separated by
 * comma).
 *
 * @param scope Builtin scope.
 * @param files Files (separated by comma).
 * @return QString Qss content.
 */
TDE_PUBLIC QString
generate(Scope scope, const QString& files);
}

TDE_INLINE tde::assets::styles::Scope
operator|(tde::assets::styles::Scope lhs, tde::assets::styles::Scope rhs)
{
  return static_cast<tde::assets::styles::Scope>(static_cast<uint8_t>(lhs) |
                                                 static_cast<uint8_t>(rhs));
}
