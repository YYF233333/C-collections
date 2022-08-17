cmake_minimum_required(VERSION 3.5)
set(CXX_STANDARD_REQUIRED 11)
set(CMAKE_CXX_FLAGS   "-g")
set(CMAKE_CXX_FLAGS   "-Wall")

project(collections)

include_directories(${CMAKE_SOURCE_DIR}/export)
include_directories(${CMAKE_SOURCE_DIR}/include)

add_subdirectory(src/core)