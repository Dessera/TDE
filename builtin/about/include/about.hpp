/**
 * @file about.hpp
 * @author Dessera (dessera@qq.com)
 * @brief About widgets.
 * @version 0.1.0
 * @date 2025-07-07
 *
 * @copyright Copyright (c) 2025 Dessera
 *
 */

#pragma once

#include <qlabel.h>
#include <qwidget.h>
#include <tde/settings.hpp>

/**
 * @brief About main widget.
 *
 */
class AboutWidget : public QWidget
{
  Q_OBJECT

private:
  tde::DesktopSettings _settings;

public:
  /**
   * @brief Construct a new About Widget object.
   *
   * @param parent Parent object.
   */
  AboutWidget(QWidget* parent = nullptr);

  ~AboutWidget() override = default;

private:
  /**
   * @brief Create a header label.
   *
   * @param text Text of the label.
   * @return QLabel* Created label.
   */
  QLabel* _header(const QString& text);
};

/**
 * @brief About header widget.
 *
 */
class AboutHeaderWidget : public QWidget
{
  Q_OBJECT

public:
  /**
   * @brief Construct a new About Header Widget object.
   *
   * @param parent Parent object.
   */
  AboutHeaderWidget(QWidget* parent = nullptr);

  ~AboutHeaderWidget() override = default;
};
