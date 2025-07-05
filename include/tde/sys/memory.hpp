/**
 * @file memory.hpp
 * @author Dessera (dessera@qq.com)
 * @brief Memory info utility.
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

/**
 * @brief Memory info.
 *
 */
struct MemoryInfo
{
  std::uintptr_t total{ 0 };
  std::uintptr_t free{ 0 };
  std::uintptr_t swap_total{ 0 };
  std::uintptr_t swap_free{ 0 };
};

/**
 * @brief Query memory info.
 *
 * @return MemoryInfo Memory info.
 */
TDE_PUBLIC MemoryInfo
query_memory_info();

}
