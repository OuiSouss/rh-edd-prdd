add_library(data STATIC list.c)

add_executable(test-list test-list.c)
target_link_libraries(test-list data)
