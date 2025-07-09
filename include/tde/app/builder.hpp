/**
 * @file builder.hpp
 * @author Dessera (dessera@qq.com)
 * @brief Utility for building a tde application.
 * @version 0.1.0
 * @date 2025-07-09
 *
 * @copyright Copyright (c) 2025 Dessera
 *
 */

#pragma once

#include <qapplication.h>
#include <qstring.h>

#include "tde/common.hpp"
#include "tde/settings.hpp"
#include "tde/widgets/app/container.hpp"
#include "tde/widgets/style.hpp"

namespace tde::app {

/**
 * @brief Run a tde application.
 *
 * @tparam Wt Application widget type.
 * @param app_name Application name.
 * @param argc Argument count.
 * @param argv Argument vector.
 * @return int Exit code.
 */
template<typename Wt>
int
run(const QString& app_name, int argc, char** argv)
{
  using widgets::StyleFactory;
  using AppContainer = widgets::app::Container;

  auto app = QApplication{ argc, argv };
  DesktopSettings settings;

  app.setStyleSheet(StyleFactory::generate_qss(settings));

  auto* app_con = AppContainer::create<Wt>(app_name, settings);
  tde_defer(delete app_con);
  app_con->show();

  return QApplication::exec();
}

}
