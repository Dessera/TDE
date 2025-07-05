#include <cstdint>
#include <qdebug.h>
#include <qfile.h>

#include "tde/config.hpp"
#include "tde/sys/memory.hpp"

namespace {

std::uintptr_t
_get_value_from_buffer(const QString& buffer)
{
  auto parts = buffer.split(' ', Qt::SkipEmptyParts);

  if (parts.size() < 2) {
    qWarning() << "Failed to parse memory info line:" << buffer;
    return 0;
  }

  return parts.at(1).toULongLong() * 1024; // NOLINT
}

}

namespace tde::sys {

MemoryInfo
query_memory_info()
{
  auto file = QFile{ config::SYS_MEMORY_FILE };

  if (!file.open(QIODevice::ReadOnly)) {
    qWarning("Failed to open %s, memory info will be unavailable",
             config::SYS_MEMORY_FILE);
    return {};
  }

  auto res = MemoryInfo{};

  auto in = QTextStream{ &file };
  auto buffer = QString{};

  while (in.readLineInto(&buffer)) {
    if (buffer.startsWith("MemTotal:")) {
      res.total = _get_value_from_buffer(buffer);
    } else if (buffer.startsWith("MemAvailable:")) {
      res.free = _get_value_from_buffer(buffer);
    } else if (buffer.startsWith("SwapTotal:")) {
      res.swap_total = _get_value_from_buffer(buffer);
    } else if (buffer.startsWith("SwapFree:")) {
      res.swap_free = _get_value_from_buffer(buffer);
    }
  }

  return res;
}

}
