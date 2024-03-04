set(mardigraphs_FOUND TRUE)

set(mardigraphs_VERSION_MAJOR 0)
set(mardigraphs_VERSION_MINOR 1)
set(mardigraphs_VERSION_PATCH 1)
set(mardigraphs_VERSION "${mardigraphs_VERSION_MAJOR}.${mardigraphs_VERSION_MINOR}.${mardigraphs_VERSION_PATCH}")


get_filename_component(_cmake ${CMAKE_CURRENT_LIST_DIR} DIRECTORY)
get_filename_component(_share ${_cmake} DIRECTORY)
get_filename_component(mardigraphs_ROOT ${_share} DIRECTORY)

set(mardigraphs_INCLUDE_DIRS "${mardigraphs_ROOT}/include/mardigraphs")
set(mardigraphs_CMAKE_MODULES_DIR "${CMAKE_CURRENT_LIST_DIR}")

list(APPEND CMAKE_MODULE_PATH ${mardigraphs_CMAKE_MODULES_DIR})

message(STATUS "-- Found mardigraphs: ${mardigraphs_VERSION} (${mardigraphs_CMAKE_MODULES_DIR})")