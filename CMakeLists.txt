cmake_minimum_required(VERSION 3.1)
project(QG)

set(CMAKE_C_STANDARD 11)

include_directories(include/)

file(GLOB_RECURSE C_SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "src/*.c")
file(GLOB_RECURSE C_HEADER RELATIVE ${CMAKE_SOURCE_DIR} "src/*.h")
# file(GLOB_RECURSE CPP_SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "src/*.cpp")

# set(COMPILE_LIBS "cJSON" "conup")

# set(COMP_LIBS_SOURCES "")

# FOREACH(cmplib ${COMPILE_LIBS})
#  set(LIB_SOURCES "")
#  file(GLOBAL_RECURSE LIB_SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "lib/${cmplib}/*.c")
#  list(COMP_LIBS_SOURCES APPEND ${LIB_SOURCES})
#  unset(LIB_SOURCES)
# ENDFOREACH()

add_executable(game 
	${C_SOURCES} 
	${C_HEADER} 
#	${CPP_SOURCES}
)

target_compile_definitions(game PRIVATE
                                $<$<CONFIG:Debug>:_DEBUG>
                            )

set_target_properties(game PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE}")
