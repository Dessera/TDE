#include <qboxlayout.h>
#include <qlabel.h>
#include <qtversion.h>
#include <tde/common.hpp>
#include <tde/config.hpp>
#include <tde/widgets/icon.hpp>
#include <tde/widgets/style.hpp>

#include "about.hpp"
#include "tde/settings.hpp"

AboutWidget::AboutWidget(const tde::DesktopSettings& /*settings*/,
                         QWidget* parent)
  : QWidget{ parent }
{
  auto* layout = new QVBoxLayout{ this };
  layout->setContentsMargins(10, 10, 10, 10);
  layout->setSpacing(10);
  setLayout(layout);

  layout->addWidget(new AboutHeaderWidget{ this });
  layout->addWidget(
    new QLabel{ "TDE is a toy desktop for embedded systems.", this });

  layout->addWidget(_header("Build Info"));
  layout->addWidget(new QLabel{
    QString{ "Compiler: %1 %2" }.arg(TDE_CXX_NAME).arg(TDE_CXX_VERSION),
    this });
  layout->addWidget(
    new QLabel{ QString{ "Qt version: %1" }.arg(qVersion()), this });
  layout->addWidget(new QLabel{
    QString{ "Build Time: %1 %2" }.arg(__DATE__).arg(__TIME__), this });

  layout->addWidget(_header("Authors"));
  layout->addWidget(new QLabel{ "Dessera <dessera@qq.com>", this });

  layout->addWidget(_header("License"));
  layout->addWidget(new QLabel{ "TDE is licensed under the terms of the "
                                "Lesser General Public License v3.0",
                                this });

  layout->addStretch(1);
}

QLabel*
AboutWidget::_header(const QString& text)
{
  auto* label = new QLabel{ text, this };
  label->setProperty("class", "tde-title");

  return label;
}

AboutHeaderWidget::AboutHeaderWidget(QWidget* parent)
  : QWidget{ parent }
{
  using tde::widgets::IconFactory;
  using tde::widgets::IconType;
  using namespace tde::config;

  auto* layout = new QHBoxLayout{ this };
  layout->setSpacing(10);
  setLayout(layout);

  auto* icon = new QLabel{ this };
  icon->setPixmap(IconFactory::pixmap(IconType::HELP_ABOUT));
  layout->addWidget(icon);

  layout->addWidget(new QLabel{
    QString{ "%1 (version %2)" }.arg(TDE_NAME_CAPITALIZED).arg(TDE_VERSION),
    this });

  layout->addStretch(1);
}
