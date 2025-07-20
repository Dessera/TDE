#include <filesystem>
#include <optional>
#include <qdebug.h>
#include <qfile.h>
#include <qlist.h>
#include <qlogging.h>
#include <qstring.h>
#include <system_error>

#include "tde/sys/fs.hpp"

namespace tde::sys::fs {

namespace {

constexpr const char* PROC_MOUNTS_PATH = "/proc/mounts";

QList<QString>
_list_mountpoint()
{
  auto f = QFile{ PROC_MOUNTS_PATH };
  if (!f.open(QIODevice::ReadOnly)) {
    qWarning() << "Failed to open mounts file:" << f.errorString();
    return {};
  }

  auto res = QList<QString>{};
  while (!f.atEnd()) {
    auto line = QString{ f.readLine() };
    auto parts = line.split(' ', Qt::SkipEmptyParts);
    if (parts.size() < 2 || !parts[0].startsWith("/dev/")) {
      continue;
    }

    res.push_back(parts[1]);
  }

  return res;
}

std::optional<Usage>
_inspect_fs_usage(const QString& mp)
{
  namespace fs = std::filesystem;

  auto ec = std::error_code{};
  auto space = fs::space(mp.toStdString(), ec);

  if (ec) {
    qWarning("Failed to inspect space info in %s: %s",
             qPrintable(mp),
             ec.message().c_str());
    return {};
  }

  return Usage{ mp, space.capacity, space.available, space.free };
}

}

QList<Usage>
usage()
{
  auto res = QList<Usage>{};

  for (const auto& mp : _list_mountpoint()) {
    auto fs_usage = _inspect_fs_usage(mp);
    if (fs_usage.has_value()) {
      res.push_back(fs_usage.value());
    }
  }

  return res;
}

}
