lib_src = files()

lib_deps = [qt_dep]

lib_src += qt.compile_moc(headers: lib_qt_moc_src, dependencies: lib_deps)
lib_src += qt.compile_resources(sources: lib_qt_res_src)

subdir('app')
subdir('assets')
subdir('sys')
subdir('widgets')