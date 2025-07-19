#include <qboxlayout.h>
#include <qlabel.h>
#include <qstring.h>
#include <qtversion.h>
#include <tde/common.hpp>
#include <tde/config.hpp>
#include <tde/widgets/delimiter.hpp>
#include <tde/widgets/text/header.hpp>

#include "buildinfo.hpp"

BuildInfo::BuildInfo(QWidget* parent)
  : QWidget{ parent }
{
  using namespace tde::widgets;

  auto* layout = new QVBoxLayout{ this };
  setLayout(layout);

  layout->addWidget(new text::H1{ "Build Information", this });
  layout->addWidget(new HDelimiter{ this });

  layout->addWidget(new text::H6{ "Compiler Info", this });
  layout->addWidget(
    new QLabel{ QString{ "  Name:  %1" }.arg(TDE_CXX_NAME), this });
  layout->addWidget(
    new QLabel{ QString{ "  Version:  %1" }.arg(TDE_CXX_VERSION), this });

  layout->addWidget(new text::H6{ "Qt Info", this });
  layout->addWidget(
    new QLabel{ QString{ "  Version:  %1" }.arg(qVersion()), this });

  layout->addWidget(new text::H6{ "Build Info", this });
  layout->addWidget(new QLabel{
    QString{ "  TDE version:  %1" }.arg(tde::config::TDE_VERSION), this });
  layout->addWidget(new QLabel{
    QString{ "  Datetime:  %1 %2" }.arg(__DATE__).arg(__TIME__), this });

  layout->addStretch(1);
}
