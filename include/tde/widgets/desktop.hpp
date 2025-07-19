/**
 * @file desktop.hpp
 * @author Dessera (dessera@qq.com)
 * @brief Desktop widget.
 * @version 0.1.0
 * @date 2025-06-02
 *
 * @copyright Copyright (c) 2025 Dessera
 *
 */

#pragma once

#include <qlist.h>
#include <qprocess.h>
#include <qwidget.h>

#include "tde/app/fetcher.hpp"
#include "tde/app/info.hpp"
#include "tde/app/launcher.hpp"
#include "tde/common.hpp"
#include "tde/settings.hpp"

namespace tde::widgets {

/**
 * @brief Desktop widget, which is the root of UI.
 *
 */
class TDE_PUBLIC Desktop : public QWidget
{
  Q_OBJECT

public:
  using AppInfo = tde::app::Info;
  using AppFetcher = tde::app::Fetcher;
  using AppLauncher = tde::app::Launcher;

  constexpr static int DOCK_MARGIN = 5; /**< Margin for dock widget. */

private:
  AppFetcher _app_fetcher;
  AppLauncher _app_launcher;

public:
  /**
   * @brief Construct a new Desktop object.
   *
   * @param settings Desktop settings.
   * @param parent Parent widget.
   */
  Desktop(const DesktopSettings& settings, QWidget* parent = nullptr);

  ~Desktop() override = default;

private:
  /**
   * @brief Initialize UI components.
   *
   * @param settings Desktop settings.
   */
  void _init_ui(const DesktopSettings& settings);
};

}
