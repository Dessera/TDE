/**
 * @file config.hpp
 * @author Dessera (dessera@qq.com)
 * @brief Static configurations.
 * @version 0.1.0
 * @date 2025-07-05
 *
 * @copyright Copyright (c) 2025 Dessera
 *
 */

#pragma once

namespace tde::config {

constexpr const char* TDE_ORGANIZATION =
  "com.dessera"; /**< Organization of the application, used to locate the
                    config path. */

constexpr const char* TDE_NAME =
  "tde"; /**< Name of the application, used to locate the config path. */

constexpr const char* TDE_NAME_CAPITALIZED =
  "TDE"; /**< Capitalized name of the application. */

constexpr const char* TDE_VERSION = "0.1.0"; /**< Version of the application. */

constexpr int APP_ICON_SIZE = 32;

}
