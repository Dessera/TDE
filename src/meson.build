lib_src = files(
  'application.cpp',
)

lib_deps = [qt_dep]

lib_src += qt.compile_moc(headers: lib_qt_moc_src, dependencies: lib_deps)
lib_src += qt.compile_resources(sources: lib_qt_res_src)

subdir('app')
subdir('sys')
subdir('widgets')

lib = library(
  'tde',
  lib_src,
  gnu_symbol_visibility: 'hidden',
  include_directories: lib_inc,
  dependencies: lib_deps,
  cpp_args: ['-DBUILDING_TDE'],
  install: true,
)

tde_dep = declare_dependency(include_directories: lib_inc, link_with: lib, dependencies: lib_deps)