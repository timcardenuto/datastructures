cmake_minimum_required (VERSION 2.8)
project (linkedlist)

add_definitions(-DDEBUG_LINKEDLIST)

file(GLOB SOURCES "*.c")
file(GLOB HEADERS "*.h")

include_directories(${CMAKE_SOURCE_DIR})

add_executable (linkedlist ${SOURCES} ${HEADERS})
