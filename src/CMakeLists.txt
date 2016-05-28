file(GLOB SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "*.cpp")

message(STATUS "Sources: ${SOURCES}")

yamail_add_static_library(recipient_parser "${SOURCES}" "${RECIPIENT_PARSER_DEPENDENCY_LIBRARIES}")
