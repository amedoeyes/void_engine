test_sources = files()
test_dependencies = [
  subproject('catch2').get_variable('catch2_with_main_dep'),
]

void_engine_test_exec = executable(
  'void_engine_test',
  test_sources,
  include_directories: include,
  dependencies: test_dependencies,
  link_with: void_engine,
)

test('void_engine', void_engine_test_exec)
