macro(add_external_googletest URL)
    if(NOT TARGET googletest)
        include(ExternalProject)

        set_directory_properties(PROPERTIES EP_PREFIX ${CMAKE_BINARY_DIR}/external)

        if(NOT GOOGLETEST_REPOSITORY)
            set(GOOGLETEST_REPOSITORY ${URL})
        endif()

        ExternalProject_Add(
            googletest
            GIT_REPOSITORY ${GOOGLETEST_REPOSITORY}
            TIMEOUT 1
            INSTALL_COMMAND ""
            UPDATE_COMMAND ""
            LOG_DOWNLOAD ON
            LOG_CONFIGURE ON
            LOG_BUILD ON
        )
        set_target_properties(googletest PROPERTIES EXCLUDE_FROM_ALL TRUE)

        ExternalProject_Get_Property(googletest source_dir)
        include_directories(SYSTEM ${source_dir}/googletest/include)
        include_directories(SYSTEM ${source_dir}/googlemock/include)

        ExternalProject_Get_Property(googletest binary_dir)
        link_directories(${binary_dir}/googlemock)
    endif()
endmacro()


set(MY_CXX_FLAGS
  "-g"
  "-O0"
  "-Wall"
  "-Werror"
  "-Wextra"
  "-Wconversion"
  "-Wcast-qual"
  "-Woverloaded-virtual"
  "-Wctor-dtor-privacy"
  "-Wnon-virtual-dtor"
  "-Wold-style-cast"
  "-Wpacked"
  "-Wredundant-decls"
  "-fexceptions"
  "-std=gnu++11"
)

foreach(FLAG ${MY_CXX_FLAGS})
        set(CMAKE_CXX_FLAGS "${FLAG} ${CMAKE_CXX_FLAGS}")
endforeach()

add_definitions(
  -DBOOST_RESULT_OF_USE_TR1_WITH_DECLTYPE_FALLBACK
  -DBOOST_SPIRIT_USE_PHOENIX_V3
)

message("
    Configuration
    -------------
    PROJECT_NAME            = ${PROJECT_NAME}
    PROJECT_SOURCE_DIR      = ${PROJECT_SOURCE_DIR}
    PROJECT_BINARY_DIR      = ${PROJECT_BINARY_DIR}
    CMAKE_CXX_COMPILER      = ${CMAKE_CXX_COMPILER}
    CXXFLAGS                = $ENV{CXXFLAGS}
    CMAKE_CXX_FLAGS         = ${CMAKE_CXX_FLAGS}
    CPPFLAGS                = $ENV{CPPFLAGS}
    CMAKE_CPP_FLAGS         = ${CMAKE_CPP_FLAGS}
    CMAKE_INSTALL_PREFIX    = ${CMAKE_INSTALL_PREFIX}
    CMAKE_INSTALL_SHAREDIR  = ${CMAKE_INSTALL_SHAREDIR}
")


add_external_googletest("https://github.yandex-team.ru/mail/googletest.git")

set(DEPENDENCIES
  gmock
  dl
  pthread
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

file(GLOB_RECURSE TEST_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "*.cpp")
file(GLOB_RECURSE PARSER_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "from_string/*.cpp")
set(SOURCES
  ${TEST_SOURCES}
  ${PARSER_SOURCE}
)

message(STATUS "Test sources: ${SOURCES}")

set(TEST_NAME utest)

add_executable(${TEST_NAME} EXCLUDE_FROM_ALL ${SOURCES})
target_link_libraries(${TEST_NAME} ${DEPENDENCIES})
add_dependencies(${TEST_NAME} googletest)

add_custom_target(check COMMAND ${TEST_NAME} DEPENDS ${TEST_NAME})
