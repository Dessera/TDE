/**
 * @file memory.hpp
 * @author Dessera (dessera@qq.com)
 * @brief Memory status utility.
 * @version 0.1.0
 * @date 2025-07-05
 *
 * @copyright Copyright (c) 2025 Dessera
 *
 */

#pragma once

#include <cstdint>

#include "tde/common.hpp"

namespace tde::sys {

constexpr const char* SYS_MEMORY_FILE =
  "/proc/meminfo"; /**< Memory information file. */

/**
 * @brief Memory status.
 *
 */
struct MemoryStatus
{
  std::uintptr_t total{ 0 };
  std::uintptr_t free{ 0 };
  std::uintptr_t swap_total{ 0 };
  std::uintptr_t swap_free{ 0 };
};

/**
 * @brief Query memory status.
 *
 * @return MemoryInfo Memory status.
 */
TDE_PUBLIC MemoryStatus
query_memory_status();

TDE_INLINE double
bytes_to_gb(std::uintptr_t bytes)
{
  return static_cast<double>(bytes) / 1024 / 1024 / 1024;
}

}
