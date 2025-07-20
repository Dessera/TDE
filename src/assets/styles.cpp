#include <cstdint>
#include <qdebug.h>
#include <qfile.h>
#include <qmap.h>
#include <qstring.h>

#include "tde/assets/styles.hpp"

namespace tde::assets::styles {

namespace {

const QMap<Scope, QString> STYLES_MAP = {
  { Scope::DESKTOP, ":/tde/styles/desktop.qss" },
  { Scope::APPLICATION, ":/tde/styles/application.qss" },
  { Scope::COMPONENTS, ":/tde/styles/components.qss" },
};

TDE_INLINE bool
_scope_contains(Scope scope, Scope target)
{
  return static_cast<uint8_t>(scope) & static_cast<uint8_t>(target);
}

void
_extend_qss_with_file(const QString& file, QString& buffer)
{
  auto f = QFile{ file };

  if (!f.open(QIODevice::ReadOnly)) {
    qWarning("Failed to open stylesheet %s: %s",
             qPrintable(file),
             qPrintable(f.errorString()));
    return;
  }

  buffer.append(f.readAll());
  buffer.append('\n');

  qInfo() << "Load stylesheet:" << file;
}

QStringList
_get_files_with_scope(Scope scope)
{
  auto files = QStringList{};

  if (_scope_contains(scope, Scope::DESKTOP)) {
    files.append(STYLES_MAP[Scope::DESKTOP]);
  }

  if (_scope_contains(scope, Scope::APPLICATION)) {
    files.append(STYLES_MAP[Scope::APPLICATION]);
  }

  if (_scope_contains(scope, Scope::COMPONENTS)) {
    files.append(STYLES_MAP[Scope::COMPONENTS]);
  }

  return files;
}

}

QString
generate(Scope scope)
{
  return generate(_get_files_with_scope(scope));
}

QString
generate(const QStringList& files)
{
  auto buffer = QString{};

  for (const auto& file : files) {
    _extend_qss_with_file(file, buffer);
  }

  return buffer;
}

QString
generate(Scope scope, const QStringList& files)
{
  auto all_files = _get_files_with_scope(scope);
  all_files.append(files);

  return generate(all_files);
}

QString
generate(Scope scope, const QString& files)
{
  return generate(scope, files.split(',', Qt::SkipEmptyParts));
}

}
