tde_about_inc = include_directories('include')

tde_about_moc_src = files(
  'include/about.hpp',
)

tde_about_src = files(
  'src/about.cpp',
  'src/main.cpp',
)

tde_about_src += qt.compile_moc(headers: tde_about_moc_src, dependencies: [tde_dep])

executable(
  'tde_about',
  tde_about_src,
  include_directories: tde_about_inc,
  dependencies: [tde_dep],
  install: true,
)