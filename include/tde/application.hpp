#pragma once

#include <qapplication.h>

#include "tde/settings.hpp"
#include "tde/widgets/desktop.hpp"

namespace tde {

class Application : public QApplication
{
public:
  constexpr static const char* AppOrganization = "com.dessera";
  constexpr static const char* AppName = "tde";

private:
  AppSettings _settings;
  Desktop _desktop;

public:
  Application(int argc, char** argv);
  ~Application() override = default;
};

}
