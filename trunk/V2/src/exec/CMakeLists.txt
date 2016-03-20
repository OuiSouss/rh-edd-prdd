add_library(exec STATIC data.c manage_error.c opt.c parse_file.c term_mode.c xfunc.c move.c)
target_link_libraries(exec game)
