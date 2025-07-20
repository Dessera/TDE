#include <qboxlayout.h>

#include "tde/widgets/app/container.hpp"
#include "tde/widgets/app/decoration.hpp"

namespace tde::widgets::app {

Container::Container(StyleScope scope,
                     const QString& name,
                     bool decoration,
                     DesktopSettings* settings,
                     QWidget* root, // NOLINT
                     QWidget* parent)
  : QWidget{ parent }
{
  settings->setParent(this);

  root->setParent(this);
  root->setAttribute(Qt::WA_StyledBackground);

  setWindowTitle(name);
  resize(settings->desktop_width(), settings->desktop_height());

  setStyleSheet(assets::styles::generate(scope, settings->desktop_qss_path()));

  auto* layout = new QVBoxLayout{ this };
  layout->setContentsMargins(0, 0, 0, 0);
  layout->setSpacing(0);
  setLayout(layout);

  if (decoration) {
    layout->addWidget(new Decoration{ name, this });
  }

  layout->addWidget(root, 1);
}

}
