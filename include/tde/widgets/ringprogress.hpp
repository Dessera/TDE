/**
 * @file ringprogress.hpp
 * @author Dessera (dessera@qq.com)
 * @brief Simple ring progress bar widget.
 * @version 0.1.0
 * @date 2025-07-13
 *
 * @copyright Copyright (c) 2025 Dessera
 *
 */

#pragma once

#include <cstdint>
#include <qwidget.h>

#include "tde/common.hpp"

namespace tde::widgets {

/**
 * @brief Simple ring progress bar widget.
 *
 */
class TDE_PUBLIC RingProgress : public QWidget
{
  Q_OBJECT

  Q_PROPERTY(int maximum READ maximum WRITE set_maximum)
  Q_PROPERTY(int value READ value WRITE set_value NOTIFY value_changed)

  Q_PROPERTY(int start_angle READ start_angle WRITE set_start_angle)
  Q_PROPERTY(Direction direction READ direction WRITE set_direction)

  Q_PROPERTY(QString text READ text WRITE set_text)
  Q_PROPERTY(bool text_visible READ text_visible WRITE set_text_visible)

public:
  constexpr static int RING_WIDTH = 20; /**< Progress ring width. */

  /**
   * @brief Progress direction.
   *
   */
  enum class Direction : uint8_t
  {
    CLOCKWISE,
    COUNTER_CLOCKWISE
  };

private:
  int _maximum{ 100 };
  int _value{ 0 };
  int _start_angle{ 90 };
  Direction _direction{ Direction::CLOCKWISE };
  QString _text;
  bool _text_visible{ true };

public:
  /**
   * @brief Construct a new Ring Progress object.
   *
   * @param parent Parent widget.
   */
  RingProgress(QWidget* parent = nullptr);

  ~RingProgress() override = default;

  void paintEvent(QPaintEvent* event) override;

  /**
   * @brief Get the maximum value.
   *
   * @return int Maximum value.
   */
  [[nodiscard]] TDE_INLINE int maximum() const { return _maximum; }

  /**
   * @brief Set the maximum value.
   *
   * @param maximum Maximum value.
   */
  void set_maximum(int maximum);

  /**
   * @brief Get the progress value.
   *
   * @return int Progress value.
   */
  [[nodiscard]] TDE_INLINE int value() const { return _value; }

  /**
   * @brief Set the progress value.
   *
   * @param value Progress value.
   */
  void set_value(int value);

  /**
   * @brief Get the start angle.
   *
   * @return int Start angle.
   */
  [[nodiscard]] TDE_INLINE int start_angle() const { return _start_angle; }

  /**
   * @brief Set the start angle.
   *
   * @param start_angle Start angle.
   */
  void set_start_angle(int start_angle);

  /**
   * @brief Get the progress direction.
   *
   * @return Direction Progress direction.
   */
  [[nodiscard]] TDE_INLINE Direction direction() const { return _direction; }

  /**
   * @brief Set the progress direction.
   *
   * @param direction Progress direction.
   */
  void set_direction(Direction direction);

  /**
   * @brief Get the text.
   *
   * @return const QString& Text.
   */
  [[nodiscard]] TDE_INLINE auto& text() const { return _text; }

  /**
   * @brief Set the text.
   *
   * @param text Text.
   * @return const QString& Text.
   */
  void set_text(const QString& text);

  /**
   * @brief Check if the text is visible.
   *
   * @return bool True if the text is visible.
   */
  [[nodiscard]] TDE_INLINE bool text_visible() const { return _text_visible; }

  /**
   * @brief Set the text visibility.
   *
   * @param visible True if the text is visible.
   */
  void set_text_visible(bool visible);

private:
  /**
   * @brief Convert angle to Qt angle parameter (16 * angle).
   *
   * @param value Angle.
   * @return int Qt angle parameter.
   */
  static TDE_INLINE int _angle_convert(int value) { return value * 16; }

  /**
   * @brief Convert value to angle span.
   *
   * @param value Value.
   * @return int Angle span.
   */
  [[nodiscard]] TDE_INLINE int _value_to_aspan(int value) const
  {
    return (_direction == Direction::COUNTER_CLOCKWISE)
             ? (value * 360 / _maximum)
             : (-value * 360 / _maximum);
  }

  /**
   * @brief Find the center rectangle.
   *
   * @param rect Original rectangle.
   * @return QRectF Center rectangle.
   */
  [[nodiscard]] QRectF _find_center_rect(const QRectF& rect) const;

  /**
   * @brief Draw the ring background.
   *
   * @param painter Painter.
   * @param rect Drawing rectangle.
   */
  void _draw_ring_background(QPainter& painter, const QRectF& rect) const;

  /**
   * @brief Draw the ring progress.
   *
   * @param painter Painter.
   * @param rect Drawing rectangle.
   */
  void _draw_ring_progress(QPainter& painter, const QRectF& rect) const;

  /**
   * @brief Draw the ring text.
   *
   * @param painter Painter.
   * @param rect Drawing rectangle.
   */
  void _draw_ring_text(QPainter& painter, const QRectF& rect) const;

signals:
  /**
   * @brief Emitted when the value is changed.
   *
   * @param value New value.
   */
  void value_changed(int value);
};

}
