cmake_minimum_required(VERSION 2.8.12)

project(recipient_parser CXX)

include(./share/find_recipient_parser_dependencies.cmake)

find_recipient_parser_dependencies()

include_directories(
  ${PROJECT_SOURCE_DIR}/include
)
include_directories(
  SYSTEM "${RECIPIENT_PARSER_DEPENDENCY_INCLUDE_DIRS}"
)

add_subdirectory(share)
add_subdirectory(include)
add_subdirectory(tests)
