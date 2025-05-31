#include "tde/application.hpp"
#include "qapplication.h"

namespace tde {

Application::Application(int argc, char** argv)
  : QApplication{ argc, argv }
  , _settings{ AppOrganization, AppName }
  , _desktop{ _settings, nullptr }
{
  _desktop.show();
}

}
