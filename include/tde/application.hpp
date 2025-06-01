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
  AppSettings _settings{ AppOrganization, AppName };
  widgets::Desktop _desktop{ _settings, nullptr };

public:
  Application(int argc, char** argv);
  ~Application() override = default;

private:
  /**
   * @brief Initialize application styles, if `desktop/qss` is set in settings,
   * load it as extra stylesheet.
   */
  void _init_styles();
};

}
