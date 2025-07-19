#include <cstdint>
#include <qdebug.h>
#include <qfile.h>

#include "tde/assets/styles.hpp"

namespace {

class StylesHelper
{
private:
  using Scope = tde::assets::Styles::Scope;

  inline static QMap<Scope, QString> STYLES_MAP = {
    { Scope::DESKTOP, ":/tde/styles/desktop.qss" },
    { Scope::APPLICATION, ":/tde/styles/application.qss" },
    { Scope::COMPONENTS, ":/tde/styles/components.qss" },
  };

public:
  static void extend_qss_with_file(const QString& file, QString& buffer)
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

  static QStringList get_files_with_scope(Scope scope)
  {
    auto files = QStringList{};

    if (StylesHelper::scope_contains(scope, Scope::DESKTOP)) {
      files.append(STYLES_MAP[Scope::DESKTOP]);
    }

    if (StylesHelper::scope_contains(scope, Scope::APPLICATION)) {
      files.append(STYLES_MAP[Scope::APPLICATION]);
    }

    if (StylesHelper::scope_contains(scope, Scope::COMPONENTS)) {
      files.append(STYLES_MAP[Scope::COMPONENTS]);
    }

    return files;
  }

  static TDE_INLINE bool scope_contains(Scope scope, Scope target)
  {
    return static_cast<uint8_t>(scope) | static_cast<uint8_t>(target);
  }
};

}

namespace tde::assets {

QString
Styles::generate(Scope scope)
{
  return generate(StylesHelper::get_files_with_scope(scope));
}

QString
Styles::generate(const QStringList& files)
{
  auto buffer = QString{};

  for (const auto& file : files) {
    StylesHelper::extend_qss_with_file(file, buffer);
  }

  return buffer;
}

QString
Styles::generate(Scope scope, const QStringList& files)
{
  auto all_files = StylesHelper::get_files_with_scope(scope);
  all_files.append(files);

  return generate(all_files);
}

QString
Styles::generate(Scope scope, const QString& files)
{
  return generate(scope, files.split(',', Qt::SkipEmptyParts));
}

}
