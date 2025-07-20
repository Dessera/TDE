#include <qboxlayout.h>
#include <tde/assets/icons.hpp>
#include <tde/settings.hpp>
#include <tde/widgets/router.hpp>

#include "about.hpp"
#include "buildinfo.hpp"
#include "description.hpp"

About::About(const tde::DesktopSettings& /*settings*/, QWidget* parent)
  : QWidget{ parent }
{
  using tde::assets::Icons;

  auto* layout = new QVBoxLayout{ this };
  layout->setContentsMargins(0, 0, 0, 0);
  setLayout(layout);

  auto* router = new tde::widgets::Router{ this };

  router->add({ "Description", Icons::icon(Icons::Type::HELP_ABOUT) },
              new Description{ this });

  router->add({ "Build", Icons::icon(Icons::Type::FOLDER_BUILD) },
              new BuildInfo{ this });

  layout->addWidget(router);
}
