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

constexpr const char* APP_ORGANIZATION =
  "com.dessera"; /**< Organization of the application, used to locate the
                    config path. */

constexpr const char* APP_NAME =
  "tde"; /**< Name of the application, used to locate the config path. */

constexpr const char* APP_NAME_CAPITALIZED =
  "TDE"; /**< Capitalized name of the application. */

constexpr const char* APP_VERSION = "0.1.0"; /**< Version of the application. */

constexpr const char* SYS_MEMORY_FILE =
  "/proc/meminfo"; /**< Memory information file. */

constexpr const char* SYS_CPU_FILE = "/proc/stat"; /**< CPU information file. */

}
