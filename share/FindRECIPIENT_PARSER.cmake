include(find_macspg_dependencies)

if(MACSPG_INCLUDE_DIR AND MACSPG_LIBRARIES)
  set(MACSPG_FIND_QUIETLY TRUE)
endif()

find_path(MACSPG_INCLUDE_DIR
  NAMES macs_pg/macs_pg.h
  HINTS ${CMAKE_INSTALL_PREFIX}/include)

find_library(MACSPG_LIBRARY NAMES macs_pg
  HINTS ${CMAKE_INSTALL_PREFIX}
  PATH_SUFFIXES .libs lib lib64)

find_macspg_dependencies()

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(MACSPG DEFAULT_MSG
  MACSPG_LIBRARY MACSPG_INCLUDE_DIR)

if(MACSPG_FOUND)
  list(APPEND MACSPG_INCLUDE_DIR ${MACSPG_DEPENDENCY_INCLUDE_DIRS})
  list(APPEND MACSPG_LIBRARIES ${MACSPG_LIBRARY} ${MACSPG_DEPENDENCY_LIBRARIES})
endif()

mark_as_advanced(MACSPG_INCLUDE_DIR MACSPG_LIBRARIES)
