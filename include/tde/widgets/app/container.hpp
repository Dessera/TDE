/**
 * @file container.hpp
 * @author Dessera (dessera@qq.com)
 * @brief Utility class for creating a container for an application (with
 * decoration).
 * @version 0.1.0
 * @date 2025-07-09
 *
 * @copyright Copyright (c) 2025 Dessera
 *
 */

#pragma once

#include <qboxlayout.h>
#include <qstring.h>
#include <qwidget.h>
#include <type_traits>

#include "tde/common.hpp"
#include "tde/settings.hpp"
#include "tde/widgets/app/decoration.hpp"

namespace tde::widgets::app {

/**
 * @brief A container for an application (with decoration).
 *
 */
class TDE_PUBLIC Container : public QWidget
{
  Q_OBJECT

public:
  ~Container() override = default;

  /**
   * @brief Create a new container for an application.
   *
   * @tparam Wt Application widget type, required to be a QWidget subclass, and
   * constructible with DesktopSettings and QWidget*.
   * @param app_name Application name.
   * @param settings Desktop settings.
   * @param parent Parent widget.
   * @return Container* New container.
   */
  template<typename Wt,
           typename = std::enable_if_t<
             std::is_base_of_v<QWidget, Wt> &&
             std::is_constructible_v<Wt, const DesktopSettings&, QWidget*>>>
  static Container* create(const QString& app_name,
                           const DesktopSettings& settings,
                           QWidget* parent = nullptr)
  {
    auto* con = new Container{ parent };
    con->setProperty("class", "tde-app-container");

    auto* layout = new QVBoxLayout{ con };
    layout->setContentsMargins(0, 0, 0, 0);
    con->setLayout(layout);

    layout->addWidget(new Decoration{ app_name, con });
    layout->addWidget(new Wt{ settings, con }, 1);

    return con;
  }

private:
  /**
   * @brief Construct a new Container object.
   *
   * @param parent Parent widget.
   */
  Container(QWidget* parent = nullptr)
    : QWidget{ parent }
  {
  }
};

}
