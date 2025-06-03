/**
 * @file statusbar.hpp
 * @author Dessera (dessera@qq.com)
 * @brief Status bar widget and its components
 * @version 0.1.0
 * @date 2025-06-03
 *
 * @copyright Copyright (c) 2025 Dessera
 *
 */

#pragma once

#include <qlabel.h>
#include <qtoolbutton.h>
#include <qwidget.h>

#include "tde/settings.hpp"

namespace tde::widgets {

/**
 * @brief Status bar widget.
 *
 */
class StatusBar : public QWidget
{
  Q_OBJECT

public:
  /**
   * @brief Construct a new Status Bar object.
   *
   * @param settings Desktop settings.
   * @param parent Parent widget.
   */
  StatusBar(const DesktopSettings& settings, QWidget* parent = nullptr);
  ~StatusBar() override = default;

private:
  /**
   * @brief Initialize the status bar.
   *
   * @param settings Desktop settings.
   */
  void _init(const DesktopSettings& settings);

  /**
   * @brief Initialize the UI components.
   *
   * @param settings Desktop settings.
   */
  void _init_ui(const DesktopSettings& settings);
};

/**
 * @brief Start menu button.
 *
 */
class StartMenuButton : public QToolButton
{
  Q_OBJECT

public:
  constexpr static const char* StartMenuIcon =
    ":/assets/icons/start-menu.svg";           /**< Path of start menu icon. */
  constexpr static int StartMenuIconSize = 24; /**< Size of start menu icon. */

  /**
   * @brief Construct a new Start Menu Button object.
   *
   * @param parent Parent widget.
   */
  explicit StartMenuButton(QWidget* parent = nullptr);
  ~StartMenuButton() override = default;
};

/**
 * @brief Time label.
 *
 */
class TimeLabel : public QLabel
{
  Q_OBJECT

public:
  constexpr static int TimeUpdateInterval = 1000; /**< Time update interval. */

private:
  QString _format;
  QTimer* _timer;

public:
  /**
   * @brief Construct a new Time Label object.
   *
   * @param format Time format.
   * @param parent Parent widget.
   */
  explicit TimeLabel(QString format, QWidget* parent = nullptr);
  ~TimeLabel() override = default;

private slots:
  /**
   * @brief Update the time label text.
   *
   */
  void _on_timeout();
};

}
