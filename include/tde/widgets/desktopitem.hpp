#pragma once

#include <qicon.h>
#include <qpixmap.h>
#include <qtmetamacros.h>
#include <qtoolbutton.h>

namespace tde::widgets {

class DesktopItem : public QToolButton
{
  Q_OBJECT

public:
  constexpr static int IconSize = 48;

  DesktopItem(const QIcon& icon,
              const QString& name,
              QWidget* parent = nullptr);
  ~DesktopItem() override = default;
};

}
