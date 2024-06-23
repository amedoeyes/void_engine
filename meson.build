project(
  'void_engine',
  'cpp',
  version: '0.1.0',
  default_options: [
    'warning_level=3',
    'cpp_std=c++20',
    'werror=true',
    'default_library=static',
  ],
)

sources = files(
  './src/ecs/common.cpp',
  './src/ecs/entity_storage.cpp',
  './src/ecs/pool_storage.cpp',
  './src/ecs/scene.cpp',
  './src/input/input_handler.cpp',
  './src/input/keyboard.cpp',
  './src/input/mouse.cpp',
  './src/renderer/buffer.cpp',
  './src/renderer/camera/free_camera_2d.cpp',
  './src/renderer/camera/free_camera_3d.cpp',
  './src/renderer/renderer.cpp',
  './src/renderer/vertex_array.cpp',
  './src/resources/image.cpp',
  './src/resources/shader.cpp',
  './src/resources/shader_manager.cpp',
  './src/resources/texture.cpp',
  './src/resources/texture_manager.cpp',
  './src/utils/logger.cpp',
  './src/window/window.cpp',
  './src/window/window_manager.cpp',
)
include = include_directories('./include')
dependencies = [
  subproject('glm').get_variable('glm_dep'),
  subproject('glfw').get_variable('glfw_dep'),
  subproject('glad').get_variable('glad_dep'),
  subproject('libpng').get_variable('libpng_dep'),
]

add_project_arguments('-DGLFW_INCLUDE_NONE', language: 'cpp')

if get_option('buildtype').startswith('debug')
  add_project_arguments('-DDEBUG', language: 'cpp')
endif

void_engine = library(
  'void_engine',
  sources,
  include_directories: include,
  dependencies: dependencies,
)

void_engine_dep = declare_dependency(
  link_with: void_engine,
  include_directories: include,
)

if get_option('tests')
  subdir('tests')
endif
