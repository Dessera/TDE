/**
 * @file cpu.hpp
 * @author Dessera (dessera@qq.com)
 * @brief CPU info utility.
 * @version 0.1.0
 * @date 2025-07-05
 *
 * @copyright Copyright (c) 2025 Dessera
 *
 */

#pragma once

#include <ctime>

#include "tde/common.hpp"

namespace tde::sys {

/**
 * @brief CPU info.
 *
 */
struct CPUInfo
{
  std::time_t user{ 0 };
  std::time_t nice{ 0 };
  std::time_t system{ 0 };
  std::time_t idle{ 0 };
  std::time_t iowait{ 0 };
  std::time_t irq{ 0 };
  std::time_t softirq{ 0 };
};

/**
 * @brief Query CPU info.
 *
 * @return CPUInfo CPU info.
 */
TDE_PUBLIC CPUInfo
query_cpu_info();

}
