cmake_minimum_required (VERSION 2.8)
project (binaryheap)

add_definitions(-DDEBUG_BINARYHEAP)

file(GLOB SOURCES "*.c")
file(GLOB HEADERS "*.h")

include_directories(${CMAKE_SOURCE_DIR})

add_executable (binaryheap ${SOURCES} ${HEADERS})
