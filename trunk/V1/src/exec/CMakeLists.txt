add_library(exec STATIC exec.c)

install(TARGETS exec DESTINATION ${PROJECT_SOURCE_DIR}/lib)
