#pragma once

#include <qicon.h>
#include <qtmetamacros.h>
#include <qtoolbutton.h>

namespace tde::widgets {

class AppItem : public QToolButton
{
  Q_OBJECT

public:
  constexpr static int IconSize = 48;

  AppItem(const QIcon& icon, const QString& name, QWidget* parent = nullptr);
  ~AppItem() override = default;
};

}
