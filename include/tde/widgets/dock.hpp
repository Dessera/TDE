#pragma once

#include <qtmetamacros.h>
#include <qwidget.h>

#include "tde/settings.hpp"

namespace tde::widgets {

class Dock : public QWidget
{
  Q_OBJECT

public:
  Dock(const AppSettings& settings, QWidget* parent = nullptr);
  ~Dock() override = default;

private:
  void _init(const AppSettings& settings);
  void _init_ui(const AppSettings& settings);
};

}
