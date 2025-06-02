#include <qboxlayout.h>
#include <qicon.h>
#include <qlabel.h>
#include <qlogging.h>
#include <qstackedwidget.h>
#include <qwidget.h>

#include "tde/helpers/appfetcher.hpp"
#include "tde/settings.hpp"
#include "tde/widgets/appitem.hpp"
#include "tde/widgets/applist.hpp"

namespace tde::widgets {

AppList::AppList(const DesktopSettings& settings, QWidget* parent)
  : QWidget(parent)
  , _grid_size(QSize{ settings.desktop_grid_x(), settings.desktop_grid_y() })
  , _stack(new QStackedWidget{ this })
{
  _init(settings);
  _init_ui(settings);
}

void
AppList::_init(const DesktopSettings& /*settings*/)
{
  setProperty("class", "tde-app-list");
}

void
AppList::_init_ui(const DesktopSettings& /*settings*/)
{
  auto* layout = new QVBoxLayout{ this };
  setLayout(layout);

  layout->addWidget(_stack, 1);
  layout->addWidget(new QLabel{ "More", this }, 0, Qt::AlignHCenter);
}

void
AppList::_create_card()
{
  auto* card = new AppListCard{ _grid_size, this };
  connect(
    card, &AppListCard::request_launch_app, this, &AppList::request_launch_app);
  _stack->addWidget(card);
}

void
AppList::on_apps_changed(const QList<helpers::AppInfo>& apps)
{
  auto old_idx = _stack->currentIndex();

  for (auto* card : findChildren<AppListCard*>()) {
    _stack->removeWidget(card);
    card->deleteLater();
  }

  _create_card();

  for (const auto& app : apps) {
    auto* cw = dynamic_cast<AppListCard*>(_stack->currentWidget());
    cw->add_app(app);
    if (cw->is_full()) {
      _create_card();
    }
  }

  auto curr_size = _stack->count();
  _stack->setCurrentIndex(std::min(old_idx, curr_size - 1));
}

AppListCard::AppListCard(const QSize& grid_size, QWidget* parent)
  : QWidget(parent)
  , _grid_size(grid_size)
{
  setProperty("class", "tde-app-list-card");

  auto* layout = new QGridLayout{ this };
  setLayout(layout);
}

void
AppListCard::add_app(const helpers::AppInfo& app)
{
  int curr = app_count();
  if (curr >= app_size()) {
    qWarning() << "AppListCard is full, cannot add more apps";
    return;
  }

  auto* layout = dynamic_cast<QGridLayout*>(this->layout());

  auto* app_item = AppItemFactory::create(app, this);
  connect(app_item,
          &AppItem::request_launch_app,
          this,
          &AppListCard::request_launch_app);
  layout->addWidget(
    app_item, curr / _grid_size.width(), curr % _grid_size.width());
}

}
