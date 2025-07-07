project(
  'tde',
  'cpp',
  version: '0.1.0',
  default_options: ['warning_level=3', 'cpp_std=gnu++17'],
)

qt = import('qt6')
qt_dep = dependency('qt6', modules: ['Core', 'Gui', 'Widgets'])

subdir('assets')
subdir('include')
subdir('src')

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

subdir('builtin')

src = files('src/main.cpp')
deps = [tde_dep]

exe = executable(
  'tde',
  src,
  dependencies: deps,
  install: true,
)

test('tde', exe)

pkg_mod = import('pkgconfig')
pkg_mod.generate(
  name: 'tde',
  filebase: 'tde',
  description: 'Toy desktop written in Qt',
  libraries: lib,
  version: '0.1.0',
)