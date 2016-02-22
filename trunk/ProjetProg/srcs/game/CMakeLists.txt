add_library(game SHARED game.c piece.c)
set_property(TARGET game PROPERTY POSITION_INDEPENDANT_CODE 1)

add_executable(test_piece test_piece1.c)
target_link_libraries(test_piece game)
add_test(test-piece test_piece)
set_tests_properties(test_piece PROPERTIES TIMEOUT 3)
