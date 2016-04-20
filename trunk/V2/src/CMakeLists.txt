add_subdirectory(game)
add_subdirectory(exec)
add_subdirectory(data)


add_executable(rush-hour-v2 play.c)
target_link_libraries(rush-hour-v2 game exec)
set(TARGET rush-hour PROPERTIES COMPILE_FLAGS -DRUSH_HOUR)

add_executable(ane-rouge play.c)
target_link_libraries(ane-rouge game exec)

