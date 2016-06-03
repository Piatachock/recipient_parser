# macro of project defenition
macro(cmake_project PROJECT_NAME)
project(${PROJECT_NAME} CXX)

set(CMAKE_CXX_FLAGS_RELWITHDEBINFO " -g -O2 -DNDEBUG")
set(CMAKE_C_FLAGS_RELWITHDEBINFO   " -g -O2 -DNDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE " -O2 -DNDEBUG")
set(CMAKE_C_FLAGS_RELEASE   " -O2 -DNDEBUG")
set(CMAKE_CXX_FLAGS_DEBUG " -g -O0 -fprofile-arcs -ftest-coverage")
set(CMAKE_C_FLAGS_DEBUG   " -g -O0 -fprofile-arcs -ftest-coverage")

set(FLAGS
 "-Wall"
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
 "-pthread"
 "-std=gnu++11"
 "-DBOOST_RESULT_OF_USE_TR1_WITH_DECLTYPE_FALLBACK"
)

foreach(FLAG ${FLAGS})
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${FLAG}")
endforeach()

set(CMAKE_INSTALL_SYSCONFDIR etc CACHE STRING "sysconf directory path")
set(CMAKE_INSTALL_LIBDIR lib64 CACHE STRING "library path")

# http://www.cmake.org/Wiki/CMake_RPATH_handling#Always_full_RPATH
if (CMAKE_INSTALL_RPATH_USE_LINK_PATH)
    set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR}")
    message("Set RPATH explicitly to ${CMAKE_INSTALL_RPATH}")
else()
    message("Do not set RPATH exlicitly.")
endif()

endmacro()


macro(cmake_condemn_warnings)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror")
endmacro()


function(cmake_conf_libdir)
if(NOT DEFINED CMAKE_INSTALL_LIBDIR)
  set(_LIBDIR_DEFAULT "lib")
  if("${CMAKE_SIZEOF_VOID_P}" EQUAL "8")
    set(_LIBDIR_DEFAULT "lib64")
  endif()
  set(CMAKE_INSTALL_LIBDIR "${_LIBDIR_DEFAULT}"
      CACHE PATH "object code libraries (${_LIBDIR_DEFAULT})")
endif()
endfunction()


function(cmake_configuration_message)

string(TOUPPER ${CMAKE_BUILD_TYPE} UPPED_BUILD_TYPE)

message("
Configuration
-------------
PROJECT_NAME            = ${PROJECT_NAME}
PROJECT_SOURCE_DIR      = ${PROJECT_SOURCE_DIR}
PROJECT_BINARY_DIR      = ${PROJECT_BINARY_DIR}
CMAKE_C_COMPILER        = ${CMAKE_C_COMPILER}
CMAKE_CXX_COMPILER      = ${CMAKE_CXX_COMPILER}
CXXFLAGS                = $ENV{CXXFLAGS}
CMAKE_CXX_FLAGS         = ${CMAKE_CXX_FLAGS}
CPPFLAGS                = $ENV{CPPFLAGS}
CMAKE_CPP_FLAGS         = ${CMAKE_CPP_FLAGS}
LDFLAGS                 = $ENV{LDFLAGS}
CMAKE_EXE_LINKER_FLAGS  = ${CMAKE_EXE_LINKER_FLAGS}
CMAKE_INSTALL_PREFIX    = ${CMAKE_INSTALL_PREFIX}
CMAKE_INSTALL_LIBDIR    = ${CMAKE_INSTALL_LIBDIR}
CMAKE_INSTALL_SYSCONFDIR= ${CMAKE_INSTALL_SYSCONFDIR}
CMAKE_INSTALL_SHAREDIR  = ${CMAKE_INSTALL_SHAREDIR}
CMAKE_BUILD_TYPE        = ${CMAKE_BUILD_TYPE}
CMAKE_CXX_FLAGS_${UPPED_BUILD_TYPE} = ${CMAKE_CXX_FLAGS_${UPPED_BUILD_TYPE}}
CMAKE_C_FLAGS_${UPPED_BUILD_TYPE}   = ${CMAKE_C_FLAGS_${UPPED_BUILD_TYPE}}
")
endfunction()


macro(cmake_include_directories)
    set(SYSTEM_DIR "include/system")
    foreach(TMP_PATH ${ARGN})
        string(FIND ${TMP_PATH} ${SYSTEM_DIR} SYSTEM_DIR_FOUND)
        if (${SYSTEM_DIR_FOUND} EQUAL -1)
            include_directories(${TMP_PATH})
        else()
            include_directories(SYSTEM ${TMP_PATH})
        endif()
    endforeach(TMP_PATH)
endmacro()
