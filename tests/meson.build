test_sources = files(
  './ecs/component_pool.test.cpp',
  './ecs/component_pool_manager.test.cpp',
  './ecs/entity.test.cpp',
  './ecs/entity_manager.test.cpp',
  './ecs/world.test.cpp',
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
  subproject('catch2', default_options: ['tests=false']).get_variable('catch2_with_main_dep'),
]

void_engine_test_exec = executable(
  'void_engine_test',
  test_sources,
  include_directories: include,
  dependencies: dependencies + test_dependencies,
  link_with: void_engine,
)

test('void_engine', void_engine_test_exec)
