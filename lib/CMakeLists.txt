project(libs)

include("${CMAKE_FUNC_DIR}dirs.cmake")

set(subLibraries)

SUBDIRLIST(subLibraries ${PROJECT_SOURCE_DIR})

FOREACH(lib ${subLibraries})
  set(FILES_C)
  file(GLOB_RECURSE FILES_C RELATIVE ${PROJECT_SOURCE_DIR} "/${lib}/*.c")
  list(LIB_COMPILE_SOURCES APPEND ${FILES_C})
  unset(FILES_C)
ENDFOREACH()
