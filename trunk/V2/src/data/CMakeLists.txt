add_library(data STATIC list.c hashTab.c)

add_executable(test-list test-list.c)
target_link_libraries(test-list data)

add_executable(test-hashTab test-hashTab.c)
target_link_libraries(test-hashTab data)

add_test(test-list test-list)
set_tests_properties(test-list PROPERTIES TIMEOUT 3)

add_test(test-hashTab test-hashTab)
set_tests_properties(test-hashTab PROPERTIES TIMEOUT 3)
