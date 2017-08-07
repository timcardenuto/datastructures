cmake_minimum_required (VERSION 2.8)
project (binarytree)

add_definitions(-DDEBUG_BINARYTREE)

file(GLOB SOURCES "*.c")
file(GLOB HEADERS "*.h")

include_directories(${CMAKE_SOURCE_DIR})

add_executable (binarytree ${SOURCES} ${HEADERS})
