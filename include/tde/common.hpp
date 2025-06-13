/**
 * @file common.hpp
 * @author Dessera (dessera@qq.com)
 * @brief Some utility macros.
 * @version 0.1.0
 * @date 2025-06-02
 *
 * @copyright Copyright (c) 2025 Dessera
 *
 */

#pragma once

#include <memory> // IWYU pragma: keep

#define _TDE_FORWARD(x) x
#define _TDE_CONCAT(a, b) a##b

#define TDE_EXPORT __attribute__((visibility("default")))

#define _tde_defer_impl(expr, cb_name, ph_name, line)                          \
  auto _TDE_CONCAT(cb_name, line) = [&](int*) { expr; };                       \
  std::unique_ptr<int, decltype(_TDE_CONCAT(cb_name, line))> _TDE_CONCAT(      \
    ph_name, line)                                                             \
  {                                                                            \
    nullptr, _TDE_CONCAT(cb_name, line)                                        \
  }

#define tde_defer(expr)                                                        \
  _tde_defer_impl(expr, _tde_defer_cb_, _tde_defer_ph_, __LINE__)
