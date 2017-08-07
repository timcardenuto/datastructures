cmake_minimum_required (VERSION 2.8)
project (hashtable)

add_definitions(-DDEBUG_HASHTABLE)

file(GLOB SOURCES "*.c")
file(GLOB HEADERS "*.h")

include_directories(${CMAKE_SOURCE_DIR})

add_executable (hashtable ${SOURCES} ${HEADERS})
