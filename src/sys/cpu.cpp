#include <algorithm>
#include <functional>
#include <qdebug.h>
#include <qfile.h>
#include <qmap.h>

#include "tde/sys/cpu.hpp"

namespace tde::sys {

CPUStatus
query_cpu_status()
{
  auto file = QFile{ SYS_CPU_STATUS_FILE };

  if (!file.open(QIODevice::ReadOnly)) {
    qWarning("Failed to open %s, cpu status will be unavailable",
             SYS_CPU_STATUS_FILE);
    return {};
  }

  auto line = file.readLine();
  if (!line.startsWith("cpu ")) {
    qWarning() << "Failed to parse cpu status line:" << line;
    return {};
  }

  auto parts = QString{ line }.split(' ', Qt::SkipEmptyParts).mid(1);
  if (parts.size() < 10) { // NOLINT
    qWarning() << "Failed to parse cpu status line:" << line;
    return {};
  }

  auto conv_result = QList<bool>{};
  auto conv_parts = QList<std::time_t>{};
  for (const auto& part : parts.mid(0, 10)) {
    bool ok = false;
    auto value = static_cast<std::time_t>(part.toLongLong(&ok));
    conv_result.append(ok);
    conv_parts.append(value);
  }

  if (std::any_of(conv_result.begin(), conv_result.end(), std::logical_not{})) {
    qWarning() << "Failed to parse cpu status line:" << line;
    return {};
  }

  return { conv_parts[0], conv_parts[1], conv_parts[2], conv_parts[3],
           conv_parts[4], conv_parts[5], conv_parts[6], conv_parts[7],
           conv_parts[8], conv_parts[9] };
}

double
get_cpu_usage(const CPUStatus& prev, const CPUStatus& curr)
{
  auto previdle = prev.idle + prev.iowait;
  auto idle = curr.idle + curr.iowait;

  auto prevbusy =
    prev.user + prev.nice + prev.system + prev.irq + prev.softirq + prev.steal;
  auto busy =
    curr.user + curr.nice + curr.system + curr.irq + curr.softirq + curr.steal;

  auto prev_total = previdle + prevbusy;
  auto total = idle + busy;

  auto totald = total - prev_total;
  auto idled = idle - previdle;

  return 1.0 - (static_cast<double>(idled) / static_cast<double>(totald));
}

QList<CPUInfo>
query_cpu_info()
{
  auto file = QFile{ SYS_CPU_INFO_FILE };
  if (!file.open(QIODevice::ReadOnly)) {
    qWarning("Failed to open %s, cpu info will be unavailable",
             SYS_CPU_INFO_FILE);
    return {};
  }

  auto data = QString{ file.readAll() };
  auto cpus_data = data.split("\n\n", Qt::SkipEmptyParts);

  auto res = QList<CPUInfo>{};
  for (const auto& cpu_data : cpus_data) {
    auto cpu_info = CPUInfo{};
    auto lines = cpu_data.split('\n', Qt::SkipEmptyParts);

    for (const auto& line : lines) {
      auto parts = line.split(':');
      if (parts.size() != 2) {
        qWarning() << "Failed to parse cpu info line:" << line;
        continue;
      }

      if (parts[0].startsWith("processor")) {
        cpu_info.processor = parts[1].trimmed().toLongLong();
      }

      if (parts[0].startsWith("model name")) {
        cpu_info.model_name = parts[1].trimmed();
      }
    }

    res.append(cpu_info);
  }

  return res;
}

QString
get_cpu_info_summary(const QList<CPUInfo>& cpu_info)
{
  auto res = QString{};
  auto cpu_map = QMap<QString, std::size_t>{};

  for (const auto& info : cpu_info) {
    cpu_map[info.model_name]++;
  }

  for (const auto& [model, count] : cpu_map.asKeyValueRange()) {
    res += QString{ "%1 x %2\n" }.arg(count).arg(model);
  }

  return res;
}

}
