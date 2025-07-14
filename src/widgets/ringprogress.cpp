#include <algorithm>
#include <qpainter.h>

#include "tde/widgets/ringprogress.hpp"

namespace tde::widgets {

RingProgress::RingProgress(QWidget* parent)
  : QWidget{ parent }
{
}

void
RingProgress::paintEvent(QPaintEvent* /*event*/)
{
  auto p = QPainter{ this };
  p.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

  auto draw_area = _find_center_rect(rect());

  _draw_ring_background(p, draw_area);
  _draw_ring_progress(p, draw_area);

  if (_text_visible) {
    _draw_ring_text(p, draw_area);
  }
}

void
RingProgress::set_maximum(int maximum)
{
  if (maximum != _maximum) {
    _maximum = maximum;
    update();
  }
}

void
RingProgress::set_value(int value)
{
  if (value != _value) {
    _value = std::min(value, _maximum);
    update();
  }
}

void
RingProgress::set_start_angle(int start_angle)
{
  if (start_angle != _start_angle) {
    _start_angle = start_angle;
    update();
  }
}

void
RingProgress::set_direction(Direction direction)
{
  if (direction != _direction) {
    _direction = direction;
    update();
  }
}

void
RingProgress::set_text(const QString& text)
{
  if (text != _text) {
    _text = text;
    update();
  }
}

void
RingProgress::set_text_visible(bool visible)
{
  if (visible != _text_visible) {
    _text_visible = visible;
    update();
  }
}

QRectF
RingProgress::_find_center_rect(const QRectF& rect) const
{
  auto rect_side = std::min(rect.width(), rect.height());
  auto res = QRectF{ (rect.width() - rect_side) / 2.0,
                     (rect.height() - rect_side) / 2.0,
                     rect_side,
                     rect_side };

  res.adjust(RING_WIDTH, RING_WIDTH, -RING_WIDTH, -RING_WIDTH);

  return res;
}

void
RingProgress::_draw_ring_background(QPainter& painter, const QRectF& rect) const
{
  auto bg_pen = QPen{};
  bg_pen.setColor(palette().color(QPalette::Base));
  bg_pen.setWidth(RING_WIDTH);
  bg_pen.setJoinStyle(Qt::RoundJoin);
  bg_pen.setCapStyle(Qt::RoundCap);

  painter.setPen(bg_pen);
  painter.drawArc(rect, 0, _angle_convert(360));

  painter.setPen(Qt::NoPen);
}

void
RingProgress::_draw_ring_progress(QPainter& painter, const QRectF& rect) const
{
  auto progress_pen = QPen{};
  progress_pen.setColor(palette().color(QPalette::Highlight));
  progress_pen.setWidth(RING_WIDTH);
  progress_pen.setJoinStyle(Qt::RoundJoin);
  progress_pen.setCapStyle(Qt::RoundCap);

  painter.setPen(progress_pen);
  painter.drawArc(rect,
                  _angle_convert(_start_angle),
                  _angle_convert(_value_to_aspan(_value)));

  painter.setPen(Qt::NoPen);
}

void
RingProgress::_draw_ring_text(QPainter& painter, const QRectF& rect) const
{
  auto text_pen = QPen{};
  text_pen.setColor(palette().color(QPalette::Text));

  painter.setPen(text_pen);
  painter.drawText(rect, Qt::AlignCenter, _text);

  painter.setPen(Qt::NoPen);
}

}
