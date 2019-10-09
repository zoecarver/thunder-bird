cmake_minimum_required(VERSION 3.2)

set(PRJ_NAME thunder)
set(PRJ_TYPE_EXECUTABLE 1)
set(PRJ_BUILD_LIBRARY 1)
set(PRJ_MAIN_FILE "main.cxx")

set (CMAKE_CXX_FLAGS 										 "-std=c++2a -ftemplate-depth=1000")
set (CMAKE_CXX_FLAGS_DEBUG_INIT          "-g")
set (CMAKE_CXX_FLAGS_MINSIZEREL_INIT     "-Os -DNDEBUG")
set (CMAKE_CXX_FLAGS_RELEASE_INIT        "-O3 -DNDEBUG")
set (CMAKE_CXX_FLAGS_RELWITHDEBINFO_INIT "-O3 -g")

# Libraries to link
set(LINK_LIBS "")
# Define cflags
set(CFLAGS "")
# Define header include directories as list
set(INCLUDE_DIR )

project(${PRJ_NAME})

add_subdirectory(src)
