cmake_minimum_required (VERSION 2.8)
project (skiplist)

add_definitions(-DDEBUG_SKIPLIST)

file(GLOB SOURCES "*.c")
file(GLOB HEADERS "*.h")

include_directories(${CMAKE_SOURCE_DIR})

add_executable (skiplist ${SOURCES} ${HEADERS})
