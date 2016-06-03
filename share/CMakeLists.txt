set(SOURCES
    find_recipient_parser_dependencies.cmake
    FindRECIPIENT_PARSER.cmake
)

set(CMAKE_INSTALL_SHAREDIR share CACHE STRING "share directory path")
install(FILES ${SOURCES} DESTINATION ${CMAKE_INSTALL_SHAREDIR}/cmake_helpers)
