project(mardigraphs)
cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD_REQUIRED 11)

set(MARDIGRAPHS_FOUND YES)
set(MARDIGRAPHS_INCLUDE_DIRS
  headers
  headers/src
  CACHE INTERNAL ""
)

include_directories(${MARDIGRAPHS_INCLUDE_DIRS})

add_executable(test_build test/test_build.cpp)