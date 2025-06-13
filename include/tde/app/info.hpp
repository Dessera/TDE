/**
 * @file info.hpp
 * @author Dessera (dessera@qq.com)
 * @brief Application information.
 * @version 0.1.0
 * @date 2025-06-12
 *
 * @copyright Copyright (c) 2025 Dessera
 *
 */

#pragma once

#include <qstring.h>

namespace tde::app {

/**
 * @brief Application information.
 *
 */
struct Info
{
  QString name;
  QString exec;
  QString icon;
};

}
