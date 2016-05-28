file(GLOB SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "*.cpp")

include_directories(
    ${GTEST_INCLUDE_DIR}
    ${GMOCK_INCLUDE_DIR}
)

add_executable(${MODULE}-test EXCLUDE_FROM_ALL ${SOURCES} )

add_dependencies(${MODULE}-test googletest googlemock)

find_package(Threads)

target_link_libraries(${MODULE}-test
    ${MODULE}
    ${GTEST_LIBRARIES}
    ${GMOCK_LIBRARIES}
    ${CMAKE_THREAD_LIBS_INIT}
)

add_test(
    NAME ${MODULE}_test
    COMMAND ${MODULE}-test
)
