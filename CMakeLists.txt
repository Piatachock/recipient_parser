cmake_minimum_required(VERSION 2.8.12)

include(./share/find_recipient_parser_dependencies.cmake)
include(./share/cmake_helpers.cmake)

cmake_project(recipient_parser)
cmake_condemn_warnings()
cmake_conf_libdir()
cmake_configuration_message()

find_recipient_parser_dependencies()

cmake_include_directories(
  ${PROJECT_SOURCE_DIR}/include
  "${RECIPIENT_PARSER_DEPENDENCY_INCLUDE_DIRS}"
)

add_subdirectory(share)
add_subdirectory(include)
add_subdirectory(tests)
