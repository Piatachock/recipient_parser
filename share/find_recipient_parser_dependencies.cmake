function(find_recipient_parser_dependencies)

find_path(BOOST_INCLUDE_DIR
  NAMES boost/spirit/include/qi.hpp
  HINTS ${CMAKE_INSTALL_PREFIX}/include/system
)

set(RECIPIENT_PARSER_DEPENDENCY_INCLUDE_DIRS
    ${BOOST_INCLUDE_DIR}
    CACHE INTERNAL ""
)

message(STATUS "Found depenedency include dirs: ${RECIPIENT_PARSER_DEPENDENCY_INCLUDE_DIRS}")

endfunction()
