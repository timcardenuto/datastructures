cmake_minimum_required (VERSION 2.8)
project (aatree)

add_definitions(-DDEBUG_AATREE)

file(GLOB SOURCES "*.c")
file(GLOB HEADERS "*.h")

include_directories(${CMAKE_SOURCE_DIR})

add_executable (aatree ${SOURCES} ${HEADERS})
