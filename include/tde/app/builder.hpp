/**
 * @file builder.hpp
 * @author Dessera (dessera@qq.com)
 * @brief Utility for building a tde application.
 * @version 0.1.0
 * @date 2025-07-09
 *
 * @copyright Copyright (c) 2025 Dessera
 *
 */

#pragma once

#include <qstring.h>

#include "tde/assets/styles.hpp"
#include "tde/settings.hpp"
#include "tde/widgets/app/container.hpp"

namespace tde::app {

/**
 * @brief Check if class is a root widget.
 *
 * @tparam Wt Class derived from QWidget.
 */
template<typename Wt>
using IsRootWidget = std::enable_if_t<
  std::is_base_of_v<QWidget, Wt> &&
  std::is_constructible_v<Wt, const DesktopSettings&, QWidget*>>;

/**
 * @brief Root widget builder.
 *
 * @tparam Wt Class derived from QWidget.
 */
template<typename Wt, typename = IsRootWidget<Wt>>
class Builder
{
public:
  using Styles = assets::Styles;
  using AppContainer = widgets::app::Container;

private:
  Styles::Scope _scope{ Styles::Scope::ALL };
  QString _name{ "TDE App" };
  bool _decoration{ true };

public:
  /**
   * @brief Set style scope.
   *
   * @param scope Style scope.
   * @return Builder<Wt> Current builder.
   */
  Builder<Wt> with_scope(Styles::Scope scope)
  {
    _scope = scope;
    return *this;
  }

  /**
   * @brief Set app name.
   *
   * @param name App name.
   * @return Builder<Wt> Current builder.
   */
  Builder<Wt> with_name(QString name)
  {
    _name = std::move(name);
    return *this;
  }

  /**
   * @brief Set decoration visibility.
   *
   * @param decoration Decoration visibility.
   * @return Builder<Wt> Current builder.
   */
  Builder<Wt> with_decoration(bool decoration)
  {
    _decoration = decoration;
    return *this;
  }

  /**
   * @brief Build widget.
   *
   * @return AppContainer Application widget wrapper.
   */
  AppContainer build()
  {
    auto* settings = new DesktopSettings{};
    auto* root = new Wt{ *settings, nullptr };

    return AppContainer{ _scope, _name, _decoration, settings, root };
  }
};

}
