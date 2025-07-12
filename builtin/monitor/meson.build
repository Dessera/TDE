tde_monitor_inc = include_directories('include')

tde_monitor_moc_src = files(
  'include/monitor.hpp',
)

tde_monitor_src = files(
  'src/main.cpp',
  'src/monitor.cpp',
)

tde_monitor_src += qt.compile_moc(headers: tde_monitor_moc_src, dependencies: [tde_dep])

executable(
  'tde_monitor',
  tde_monitor_src,
  include_directories: tde_monitor_inc,
  dependencies: [tde_dep],
  install: true,
)