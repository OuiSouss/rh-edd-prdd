cmake_minimum_required(VERSION 2.6)
projet(ProjetProg)

include_directories(include)
add_definitions(-std=gnu99 -Wall -Wextra)
add_subdirectory(src)

install(TARGETS game DESTINATION lib)
