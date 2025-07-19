#include <qboxlayout.h>
#include <tde/settings.hpp>
#include <tde/widgets/icon.hpp>
#include <tde/widgets/router.hpp>

#include "about.hpp"
#include "buildinfo.hpp"
#include "description.hpp"

About::About(const tde::DesktopSettings& /*settings*/, QWidget* parent)
  : QWidget{ parent }
{
  using tde::widgets::IconFactory;
  using tde::widgets::IconType;

  auto* layout = new QVBoxLayout{ this };
  layout->setContentsMargins(0, 0, 0, 0);
  setLayout(layout);

  auto* router = new tde::widgets::Router{ this };

  router->add({ "Description", IconFactory::icon(IconType::HELP_ABOUT) },
              new Description{ this });

  router->add({ "Build", IconFactory::icon(IconType::FOLDER_BUILD) },
              new BuildInfo{ this });

  layout->addWidget(router);
}
