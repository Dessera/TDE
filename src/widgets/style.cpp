#include <qdebug.h>
#include <qfile.h>

#include "tde/widgets/style.hpp"

namespace tde::widgets {

QString
StyleFactory::generate_qss(const QStringList& files)
{
  auto buffer = QString{};

  _read_qss(DEFAULT_STYLE, buffer);

  for (const auto& file : files) {
    _read_qss(file, buffer);
  }

  return buffer;
}

QString
StyleFactory::generate_qss(const DesktopSettings& settings)
{
  if (settings.desktop_qss_path().isEmpty()) {
    return generate_qss();
  }

  return generate_qss({ settings.desktop_qss_path() });
}

void
StyleFactory::_read_qss(const QString& file, QString& buffer)
{
  auto f = QFile{ file };

  if (!f.open(QIODevice::ReadOnly)) {
    qWarning("Failed to open stylesheet %s: %s",
             qPrintable(file),
             qPrintable(f.errorString()));
    return;
  }

  buffer.append(f.readAll());

  qInfo() << "Load stylesheet:" << file;
}

}
