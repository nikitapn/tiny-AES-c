cmake_minimum_required(VERSION 3.28.1)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

project(aes-test)

add_library(tiny-aes STATIC)
target_sources(tiny-aes
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/aes.c
    INTERFACE
        ${CMAKE_CURRENT_LIST_DIR}/aes.h
        ${CMAKE_CURRENT_LIST_DIR}/aes.hpp
)

include_directories(tiny-aes
    INTERFACE
        ${CMAKE_CURRENT_LIST_DIR}
)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(aes-test tests/main.cpp)
target_include_directories(aes-test PUBLIC ./)
target_link_libraries(aes-test PUBLIC tiny-aes)


if (EMSCRIPTEN)
  set(CMAKE_EXECUTABLE_SUFFIX .html)
  #  set_property(TARGET profiler PROPERTY LINK_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/shell.html)
  target_link_options(aes-test PUBLIC 
    -sWASM=0
  # --shell-file=${CMAKE_CURRENT_SOURCE_DIR}/src/shell.html
  )
endif()



