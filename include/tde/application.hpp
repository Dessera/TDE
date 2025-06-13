/**
 * @file application.hpp
 * @author Dessera (dessera@qq.com)
 * @brief QApplication wrapper, for initializing settings and styles.
 * @version 0.1.0
 * @date 2025-06-02
 *
 * @copyright Copyright (c) 2025 Dessera
 *
 */

#pragma once

#include <qapplication.h>

#include "tde/app/fetcher.hpp"
#include "tde/app/launcher.hpp"
#include "tde/common.hpp"
#include "tde/settings.hpp"
#include "tde/widgets/desktop.hpp"

namespace tde {

/**
 * @brief Application for managing UI and other features.
 *
 */
class TDE_EXPORT Application : public QApplication
{
public:
  constexpr static const char* AppOrganization =
    "com.dessera"; /**< Organization of the application, used to locate the
                      config path. */
  constexpr static const char* AppName =
    "tde"; /**< Name of the application, used to locate the config path. */
  constexpr static const char* AppStyleSheet =
    ":/styles/style.qss"; /**< Path to the default stylesheet. */

private:
  DesktopSettings _settings{ AppOrganization, AppName };
  widgets::Desktop _desktop{ _settings };
  app::Fetcher _app_fetcher{ _settings };
  app::Launcher _app_launcher;

public:
  /**
   * @brief Construct a new Application object.
   *
   * @param argc Number of arguments.
   * @param argv Arguments.
   */
  Application(int argc, char** argv);
  ~Application() override = default;

private:
  /**
   * @brief Initialize application.
   */
  void _init();

  /**
   * @brief Initialize application styles, if `desktop/qss_path` is set in
   * settings, load it as extra stylesheet.
   */
  void _init_styles();
};

}
