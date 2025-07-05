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
#include "tde/config.hpp"
#include "tde/settings.hpp"
#include "tde/widgets/desktop.hpp"

namespace tde {

/**
 * @brief Application for managing UI and other features.
 *
 */
class TDE_PUBLIC Application : public QApplication
{
  Q_OBJECT

private:
  DesktopSettings _settings{ config::APP_ORGANIZATION, config::APP_NAME };

  app::Fetcher _app_fetcher{ _settings.desktop_app_path() };
  app::Launcher _app_launcher;

  widgets::Desktop _desktop{ _settings };

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
