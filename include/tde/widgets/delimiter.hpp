#pragma once

#include <qwidget.h>

#include "tde/common.hpp"

namespace tde::widgets {

class TDE_PUBLIC HDelimiter : public QWidget
{
  Q_OBJECT

public:
  explicit HDelimiter(QWidget* parent = nullptr)
    : QWidget{ parent }
  {
    setAttribute(Qt::WA_StyledBackground);
    setFixedHeight(1);
  }

  ~HDelimiter() override = default;
};

class TDE_PUBLIC VDelimiter : public QWidget
{
  Q_OBJECT

public:
  explicit VDelimiter(QWidget* parent = nullptr)
    : QWidget{ parent }
  {
    setAttribute(Qt::WA_StyledBackground);
    setFixedWidth(1);
  }

  ~VDelimiter() override = default;
};

}
