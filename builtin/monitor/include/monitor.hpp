#pragma once

#include <qtimer.h>
#include <qwidget.h>
#include <tde/settings.hpp>

class Monitor : public QWidget
{
  Q_OBJECT

private:
  QTimer* _tim;

public:
  Monitor(const tde::DesktopSettings& settings, QWidget* parent = nullptr);

  ~Monitor() override = default;

private slots:
  void _on_timeout();
};