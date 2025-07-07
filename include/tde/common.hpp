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
#define _TDE_STR_IMPL(x) #x
#define _TDE_STR(x) _TDE_STR_IMPL(x)

#if defined _WIN32 || defined __CYGWIN__
#ifdef BUILDING_TDE
#define TDE_PUBLIC __declspec(dllexport)
#else
#define TDE_PUBLIC __declspec(dllimport)
#endif
#else
#ifdef BUILDING_TDE
#define TDE_PUBLIC __attribute__((visibility("default")))
#else
#define TDE_PUBLIC
#endif
#endif

#if defined _WIN32 || defined __CYGWIN__
#define TDE_INLINE inline __forceinline
#else
#define TDE_INLINE inline __attribute__((always_inline))
#endif

#if defined __clang__
#define TDE_CXX_NAME "Clang "
#define TDE_CXX_VERSION __clang_version__
#elif defined __GNUC__
#define TDE_CXX_NAME "GCC "
#define TDE_CXX_VERSION                                                        \
  _TDE_STR(__GNUC__)                                                           \
  "." _TDE_STR(__GNUC_MINOR__) "." _TDE_STR(__GNUC_PATCHLEVEL__)
#else
#defube TDE_CXX_NAME "unknown "
#define TDE_CXX_VERSION "unknown"
#endif

// NOLINTNEXTLINE
#define _tde_defer_impl(expr, cb_name, ph_name, line)                          \
  auto _TDE_CONCAT(cb_name, line) = [&](int*) { expr; };                       \
  std::unique_ptr<int, decltype(_TDE_CONCAT(cb_name, line))> _TDE_CONCAT(      \
    ph_name, line)                                                             \
  {                                                                            \
    nullptr, _TDE_CONCAT(cb_name, line)                                        \
  }

// NOLINTNEXTLINE
#define tde_defer(expr)                                                        \
  _tde_defer_impl(expr, _tde_defer_cb_, _tde_defer_ph_, __LINE__)
