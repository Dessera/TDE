#pragma once

#include <qwidget.h>

#include "tde/settings.hpp"

namespace tde {

class Desktop : public QWidget
{
  Q_OBJECT

public:
  Desktop(const AppSettings& settings, QWidget* parent = nullptr);
  ~Desktop() override = default;

private:
  void _init(const AppSettings& settings);
  void _init_ui(const AppSettings& settings);
};

}
