lib_src = files(
  'application.cpp',
  'settings.cpp',
)

lib_inc = include_directories('../include')
lib_deps = [qt_dep]

lib_src += qt.compile_moc(headers: lib_qt_moc_src, dependencies: lib_deps)
lib_src += qt.compile_resources(sources: lib_qt_res_src)

subdir('app')
subdir('widgets')

lib = library(
  'tde',
  lib_src,
  gnu_symbol_visibility: 'hidden',
  include_directories: lib_inc,
  dependencies: lib_deps,
  install: true,
)

dep_tde = declare_dependency(include_directories: lib_inc, link_with: lib, dependencies: lib_deps)