add_library(game STATIC game.c piece.c)


add_executable(test-piece-v2 test-piece.c)
target_link_libraries(test-piece-v2 game)

add_executable(test-game-v2 test-game.c)
target_link_libraries(test-game-v2 game)

add_executable(solveur solve.c)
target_link_libraries(solveur game)

enable_testing()
add_test(test-piece test-piece-v2)
set_tests_properties(test-piece PROPERTIES TIMEOUT 3)

add_test(test-game test-game-v2)
set_tests_properties(test-game PROPERTIES TIMEOUT 3)
