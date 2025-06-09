project(
  'tde',
  'cpp',
  version: '0.1.0',
  default_options: ['warning_level=3', 'cpp_std=gnu++26'],
)

qt = import('qt6')
qt_dep = dependency('qt6', modules: ['Core', 'Gui', 'Widgets'])

subdir('assets')
subdir('include')
subdir('src')

inc = include_directories('include')
src = files('src/main.cpp')
deps = [dep_tde]

exe = executable(
  'tde',
  src,
  include_directories: inc,
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