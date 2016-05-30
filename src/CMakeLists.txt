file(GLOB SOURCES RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "from_string/*.cpp")

message(STATUS "Sources: ${SOURCES}")

yamail_add_static_library(recipient_parser-from_string "${SOURCES}" "${RECIPIENT_PARSER_DEPENDENCY_LIBRARIES}")
