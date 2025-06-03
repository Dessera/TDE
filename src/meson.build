lib_src = files(
  'helpers/appfetcher.cpp',
  'helpers/applauncher.cpp',
  'widgets/appitem.cpp',
  'widgets/applist.cpp',
  'widgets/desktop.cpp',
  'widgets/dock.cpp',
  'widgets/radioselector.cpp',
  'widgets/statusbar.cpp',
  'application.cpp',
  'settings.cpp',
)
lib_inc = include_directories('../include')
lib_deps = [qt_dep]

lib_src += qt.compile_moc(headers: lib_qt_moc_src, dependencies: lib_deps)
lib_src += qt.compile_resources(sources: lib_qt_res_src)

lib = library(
  'tde',
  lib_src,
  include_directories: lib_inc,
  dependencies: lib_deps,
  install: true,
)

dep_tde = declare_dependency(include_directories: lib_inc, link_with: lib, dependencies: lib_deps)