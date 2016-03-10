add_library(exec STATIC exec.c)
# add_library(exec SHARED exec.c)
target_link_libraries(exec game)

