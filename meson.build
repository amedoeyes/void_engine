project(
  'void_engine',
  'cpp',
  version: '0.1.0',
  default_options: [
    'warning_level=3',
    'cpp_std=c++20',
    'prefer_static=true',
    'werror=true',
  ],
)

sources = files()
include = include_directories('./include')
dependencies = [
  subproject('glm').get_variable('glm_dep'),
  subproject('glfw').get_variable('glfw_dep'),
  subproject('glad').get_variable('glad_dep'),
]

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
