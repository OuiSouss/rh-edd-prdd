cmake_minimum_required(VERSION 2.6)
project(rh-edd-pp)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/lib")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}")

include_directories(include)
add_definitions(-std=gnu99 -Wall -Wextra)
# set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-rpath -Wl,${PROJECT_SOURCE_DIR}/lib")
# set(CMAKE_POSITION_INDEPENDENT_CODE 1)
# set(CMAKE_INSTALL_RPATH "${PROJECT_SOURCE_DIR}/lib")
# set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
add_subdirectory(src)
