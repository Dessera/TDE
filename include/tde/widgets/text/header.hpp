/**
 * @file header.hpp
 * @author Dessera (dessera@qq.com)
 * @brief H1-H6 components for TDE apps.
 * @version 0.1.0
 * @date 2025-07-19
 *
 * @copyright Copyright (c) 2025 Dessera
 *
 */

#pragma once

#include <qlabel.h>

#include "tde/common.hpp"

namespace tde::widgets::text {

class TDE_PUBLIC H1 : public QLabel
{
  Q_OBJECT

public:
  H1(QWidget* parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags{})
    : H1{ {}, parent, f }
  {
  }

  H1(const QString& text,
     QWidget* parent = nullptr,
     Qt::WindowFlags f = Qt::WindowFlags{})
    : QLabel{ text, parent, f }
  {
  }

  ~H1() override = default;
};

class TDE_PUBLIC H2 : public QLabel
{
  Q_OBJECT

public:
  H2(QWidget* parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags{})
    : H2{ {}, parent, f }
  {
  }

  H2(const QString& text,
     QWidget* parent = nullptr,
     Qt::WindowFlags f = Qt::WindowFlags{})
    : QLabel{ text, parent, f }
  {
  }

  ~H2() override = default;
};

class TDE_PUBLIC H3 : public QLabel
{
  Q_OBJECT

public:
  H3(QWidget* parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags{})
    : H3{ {}, parent, f }
  {
  }

  H3(const QString& text,
     QWidget* parent = nullptr,
     Qt::WindowFlags f = Qt::WindowFlags{})
    : QLabel{ text, parent, f }
  {
  }

  ~H3() override = default;
};

class TDE_PUBLIC H4 : public QLabel
{
  Q_OBJECT

public:
  H4(QWidget* parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags{})
    : H4{ {}, parent, f }
  {
  }

  H4(const QString& text,
     QWidget* parent = nullptr,
     Qt::WindowFlags f = Qt::WindowFlags{})
    : QLabel{ text, parent, f }
  {
  }

  ~H4() override = default;
};

class TDE_PUBLIC H5 : public QLabel
{
  Q_OBJECT

public:
  H5(QWidget* parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags{})
    : H5{ {}, parent, f }
  {
  }

  H5(const QString& text,
     QWidget* parent = nullptr,
     Qt::WindowFlags f = Qt::WindowFlags{})
    : QLabel{ text, parent, f }
  {
  }

  ~H5() override = default;
};

class TDE_PUBLIC H6 : public QLabel
{
  Q_OBJECT

public:
  H6(QWidget* parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags{})
    : H6{ {}, parent, f }
  {
  }

  H6(const QString& text,
     QWidget* parent = nullptr,
     Qt::WindowFlags f = Qt::WindowFlags{})
    : QLabel{ text, parent, f }
  {
  }

  ~H6() override = default;
};

}
