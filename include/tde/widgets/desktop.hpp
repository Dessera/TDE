#pragma once

#include <qwidget.h>

#include "tde/settings.hpp"

namespace tde::widgets {

class Desktop : public QWidget
{
  Q_OBJECT

public:
  constexpr static int DockMargin = 5;

  Desktop(const AppSettings& settings, QWidget* parent = nullptr);
  ~Desktop() override = default;

private:
  void _init(const AppSettings& settings);
  void _init_ui(const AppSettings& settings);
};

}
