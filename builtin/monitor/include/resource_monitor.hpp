/**
 * @file resource_monitor.hpp
 * @author Dessera (dessera@qq.com)
 * @brief Resource monitor.
 * @version 0.1.0
 * @date 2025-07-15
 *
 * @copyright Copyright (c) 2025 Dessera
 *
 */

#pragma once

#include <qtimer.h>
#include <qwidget.h>
#include <tde/sys/cpu.hpp>
#include <tde/widgets/ringprogress.hpp>

/**
 * @brief Resource usage monitor.
 *
 */
class ResourceUsageMonitor : public QWidget
{
  Q_OBJECT

public:
  constexpr static int REFRESH_INTERVAL =
    1000; /**< Refresh interval in milliseconds. */

private:
  QTimer* _tim;
  tde::widgets::RingProgress* _cpu;
  tde::widgets::RingProgress* _mem;
  tde::widgets::RingProgress* _swap;

  tde::sys::CPUStatus _cpu_prev;

public:
  /**
   * @brief Construct a new Resource Usage Monitor object.
   *
   * @param parent Parent widget.
   */
  ResourceUsageMonitor(QWidget* parent = nullptr);

  ~ResourceUsageMonitor() override = default;

  /**
   * @brief Refresh the resource monitor.
   *
   */
  void refresh();

private slots: // NOLINT
  /**
   * @brief Handles the timer timeout event.
   *
   */
  void _on_timer_timeout();
};

/**
 * @brief Resource monitor.
 *
 */
class ResourceMonitor : public QWidget
{
  Q_OBJECT

public:
  /**
   * @brief Construct a new Resource Monitor object.
   *
   * @param parent Parent widget.
   */
  ResourceMonitor(QWidget* parent = nullptr);

  ~ResourceMonitor() override = default;

private:
  /**
   * @brief Create the CPU info label.
   *
   */
  void _create_cpu_info();

  /**
   * @brief Create the memory info label.
   *
   */
  void _create_mem_info();
};
