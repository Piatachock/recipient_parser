yamail_add_external_googletest()

include_directories(${CMAKE_SOURCE_DIR}/src/)
file(GLOB_RECURSE SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "*.cpp")
message(STATUS "Test sources: ${SOURCES}")

set(CMAKE_FIND_LIBRARY_SUFFIXES ".so")
yamail_find_library(dl)

set(DEPENDENCIES
  gmock
  ${dl_LIBRARIES}
  recipient_parser-from_string
)

if (NOT TARGET check)
  add_custom_target(check COMMAND utest)
  set( BUILD_TESTS 1 )
endif()

yamail_add_test(utest "${SOURCES}" "${DEPENDENCIES}")
yamail_add_test_dependencies(utest googletest)