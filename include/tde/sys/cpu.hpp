/**
 * @file cpu.hpp
 * @author Dessera (dessera@qq.com)
 * @brief CPU status utility.
 * @version 0.1.0
 * @date 2025-07-05
 *
 * @copyright Copyright (c) 2025 Dessera
 *
 */

#pragma once

#include <cstddef>
#include <ctime>
#include <qlist.h>
#include <qstring.h>

#include "tde/common.hpp"

namespace tde::sys {

constexpr const char* SYS_CPU_STATUS_FILE =
  "/proc/stat"; /**< CPU status file. */

constexpr const char* SYS_CPU_INFO_FILE =
  "/proc/cpuinfo"; /**< CPU info file. */

/**
 * @brief CPU status.
 *
 */
struct CPUStatus
{
  std::time_t user{ 0 };
  std::time_t nice{ 0 };
  std::time_t system{ 0 };
  std::time_t idle{ 0 };
  std::time_t iowait{ 0 };
  std::time_t irq{ 0 };
  std::time_t softirq{ 0 };
  std::time_t steal{ 0 };
  std::time_t guest{ 0 };
  std::time_t guest_nice{ 0 };
};

/**
 * @brief CPU info, only limited to model name and processor number for
 * convenience.
 *
 */
struct CPUInfo
{
  std::size_t processor{ 0 };
  QString model_name;
};

/**
 * @brief Query CPU info.
 *
 * @return CPUStatus CPU info.
 */
TDE_PUBLIC CPUStatus
query_cpu_status();

/**
 * @brief Get the CPU Usage.
 *
 * @param prev Previous CPU status.
 * @param curr Current CPU status.
 * @return double CPU usage.
 */
TDE_PUBLIC double
get_cpu_usage(const CPUStatus& prev, const CPUStatus& curr);

/**
 * @brief Query CPU info.
 *
 * @return QList<CPUInfo> CPU info of each processor.
 */
TDE_PUBLIC QList<CPUInfo>
query_cpu_info();

/**
 * @brief Summarize CPU info.
 *
 * @param cpu_info CPU info.
 * @return QString Summary of CPU info.
 */
TDE_PUBLIC QString
get_cpu_info_summary(const QList<CPUInfo>& cpu_info);

}
