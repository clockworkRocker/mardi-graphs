project(mardigraphs VERSION 0.0.2)
cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD_REQUIRED 11)
set(CMAKE_CXX_STANDARD 11)

set(${PROJECT_NAME}_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/include CACHE INTERNAL "")
include_directories(${${PROJECT_NAME}_INCLUDE_DIRS})

if (MSVC)

else()
  set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-Wall -Werror -Wextra")
endif(MSVC)

option(${PROJECT_NAME}_BUILD_TESTS "Build ${PROJECT_NAME} tests" OFF)

if (${PROJECT_NAME}_BUILD_TESTS)
message(STATUS "Building tests for mardigraphs...")
file(GLOB ${PROJECT_NAME}_TESTS ${PROJECT_SOURCE_DIR}/test/*.cpp)

enable_testing()
include(CTest)
foreach(testsource ${${PROJECT_NAME}_TESTS})
  get_filename_component(testname ${testsource} NAME_WE)
  add_executable(${testname} ${testsource})
  add_test(
    NAME ${testname}
    COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${testname})
endforeach(testsource ${TEST_SOURCES})

endif() # BUILD_TESTS