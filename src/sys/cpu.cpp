#include <algorithm>
#include <functional>
#include <qdebug.h>
#include <qfile.h>

#include "tde/config.hpp"
#include "tde/sys/cpu.hpp"

namespace tde::sys {

CPUInfo
query_cpu_info()
{
  auto file = QFile{ config::SYS_CPU_FILE };

  if (!file.open(QIODevice::ReadOnly)) {
    qWarning("Failed to open %s, cpu info will be unavailable",
             config::SYS_CPU_FILE);
    return {};
  }

  auto line = file.readLine();
  if (!line.startsWith("cpu ")) {
    qWarning() << "Failed to parse cpu info line:" << line;
    return {};
  }

  auto parts = QString{ line }.split(' ', Qt::SkipEmptyParts).mid(1);
  if (parts.size() < 7) { // NOLINT
    qWarning() << "Failed to parse cpu info line:" << line;
    return {};
  }

  auto conv_result = QList<bool>{};
  auto conv_parts = QList<std::time_t>{};
  for (const auto& part : parts.mid(0, 7)) {
    bool ok = false;
    auto value = static_cast<std::time_t>(part.toLongLong(&ok));
    conv_result.append(ok);
    conv_parts.append(value);
  }

  if (std::any_of(conv_result.begin(), conv_result.end(), std::logical_not{})) {
    qWarning() << "Failed to parse cpu info line:" << line;
    return {};
  }

  return {
    conv_parts[0], conv_parts[1], conv_parts[2], conv_parts[3],
    conv_parts[4], conv_parts[5], conv_parts[6],
  };
}

}
