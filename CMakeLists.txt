cmake_minimum_required(VERSION 2.8.12)

find_path(CMAKE_MODULE_PATH yamail.cmake
  HINTS ${CMAKE_INSTALL_PREFIX}/share/cmake_helpers
  /usr/share/cmake_helpers)
include(yamail)
include(./share/find_recipient_parser_dependencies.cmake)

yamail_project(recipient_parser)
yamail_condemn_warnings()
yamail_conf_libdir()
yamail_configuration_message()

find_recipient_parser_dependencies()

yamail_include_directories(
  ${PROJECT_SOURCE_DIR}/include
  "${RECIPIENT_PARSER_DEPENDENCY_INCLUDE_DIRS}"
)

add_subdirectory(share)
add_subdirectory(include)
add_subdirectory(tests)
