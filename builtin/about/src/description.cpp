#include <qboxlayout.h>
#include <qlabel.h>
#include <qstring.h>
#include <tde/widgets/delimiter.hpp>
#include <tde/widgets/text/header.hpp>

#include "description.hpp"

Description::Description(QWidget* parent)
  : QWidget{ parent }
{
  using namespace tde::widgets;

  auto* layout = new QVBoxLayout{ this };
  setLayout(layout);

  layout->addWidget(new text::H1{ "TDE", this });
  layout->addWidget(new HDelimiter{ this });

  auto* desc = new QLabel{
    "  TDE is a desktop environment written for embedded environments, based "
    "on "
    "Qt6 and Linux framebuffer, and open sourced under the LGPLv3 license. "
    "Welcome anyone to submit issues and PRs.",
    this
  };
  desc->setWordWrap(true);
  layout->addWidget(desc);

  layout->addWidget(new text::H6{ "Project Info", this });
  layout->addWidget(new QLabel{ "  Author:  Dessera <dessera@qq.com>", this });
  layout->addWidget(
    new QLabel{ "  Repo:  https://github.com/Dessera/TDE", this });

  layout->addStretch(1);
}
