cmake_minimum_required(VERSION 3.1)
project(QG VERSION 0.1 )

set(CMAKE_C_STANDARD 11)

include_directories(include/)
include_directories(lib/)
include_directories(src/)


set(CMAKE_FUNC_DIR "${CMAKE_SOURCE_DIR}/cmake/")

list(APPEND CMAKE_MODULE_PATH "./cmake/")


# Pass the project version to the C code as preprocessor defines
add_definitions(-DPROJECT_VERSION="${PROJECT_VERSION}")
add_definitions(-DPROJECT_VERSION_MAJOR=${PROJECT_VERSION_MAJOR})
add_definitions(-DPROJECT_VERSION_MINOR=${PROJECT_VERSION_MINOR})


# get all files of the project
file(GLOB_RECURSE C_SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "src/*.c")
file(GLOB_RECURSE C_HEADER RELATIVE ${CMAKE_SOURCE_DIR} "src/*.h")
# file(GLOB_RECURSE CPP_SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "src/*.cpp")

set(LIB_COMPILE_SOURCES)

add_executable(game 
	${C_SOURCES} 
	${C_HEADER} 
	"${PROJECT_SOURCE_DIR}/lib/cJSON/cJSON.c"
#	${CPP_SOURCES}
)

target_compile_definitions(game PRIVATE
                                $<$<CONFIG:Debug>:_DEBUG>
                            )

set_target_properties(game PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE}")

set_target_properties(game PROPERTIES OUTPUT_NAME "qg")
