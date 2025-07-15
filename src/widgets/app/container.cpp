
#include <qboxlayout.h>

#include "tde/widgets/app/container.hpp"

namespace tde::widgets::app {

Container::Container(QWidget* parent)
  : QWidget{ parent }
{
  setProperty("class", "tde-app-container");

  auto* layout = new QVBoxLayout{ this };
  layout->setContentsMargins(0, 0, 0, 0);
  layout->setSpacing(0);
  setLayout(layout);
}

}
