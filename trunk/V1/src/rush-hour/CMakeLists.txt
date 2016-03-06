add_executable(rush-hour-v1 rush-hour.c)
target_link_libraries(rush-hour-v1 game exec)
install(TARGETS rush-hour-v1 DESTINATION ${PROJECT_SOURCE_DIR})
