test_sources = files(
  './ecs/common.test.cpp',
  './ecs/entity_storage.test.cpp',
  './ecs/pool.test.cpp',
  './ecs/pool_storage.test.cpp',
  './ecs/scene.test.cpp',
  './ecs/view.test.cpp',
  './event/event.test.cpp',
  './event/event_listener.test.cpp',
  './event/event_manager.test.cpp',
  './resources/image.test.cpp',
  './resources/texture_manager.test.cpp',
  './utils/logger.test.cpp',
  './window/window.test.cpp',
  './window/window_manager.test.cpp',
)
test_dependencies = [
  subproject('catch2').get_variable('catch2_with_main_dep'),
]

void_engine_test_exec = executable(
  'void_engine_test',
  test_sources,
  include_directories: include,
  dependencies: dependencies + test_dependencies,
  link_with: void_engine,
)

test('void_engine', void_engine_test_exec)
