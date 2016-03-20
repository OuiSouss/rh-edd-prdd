#ifndef _DATA_H
# define _DATA_H

/**
 * @file data.h
 * @brief The header for the structure used to pass informations through
 * execution steps.
 */

# include <game.h>

# ifndef _S_DATA
#  define _S_DATA
/**
 * @struct s_data
 * @brief The custom type used to encapsulate informations needed by the program.
 */
struct s_data
{
  int ac;	/*!< A copy of the program argcount. */
  char** av;	/*!< A pointer to the array of argvalues. */

  int status;	/*!< The value used to track execution steps. */
  int* flags;	/*!< The array used to parse flags provided at input. */

  int index;	/*!< A field usefull to save the position of the next paramater to parse. */

  int width;	/*!< The field in which will be stored the width of the game. */
  int height;	/*!< The field associated with the height of the game. */

  piece* pcs;	/*!< The array of piece that will be used to start the game. */
  int nb_pcs;	/*!< The field related to the number of pieces in the game. */

  game g;	/*!< The field that will serve to store game related data. */

  bool (*game_over)(cgame);	/*!< A pointer to the function that will tell us when the game is over. */
};
# endif /* _S_DATA */

# ifndef _M_STEP
#  define _M_STEP
/**
 * @addtogroup STEP_MACROS
 * @brief Macros used to track program steps during the execution.
 * @{
 */
#  define END_STEP 0
#  define START_STEP 1
#  define LOOP_STEP 2
#  define PIECE_STEP 4
#  define MOVE_STEP 5
#  define INPUT_ERROR_STEP 6
/**@}*/
# endif /* _T_STATUS */

/**
 * @addtogroup SIZE_MACROS
 * @brief Custom macros to set a default size for buffers
 * and the maximum number of pieces supported.
 * @{
 */
# define BUFFER_SIZE 64
# define MAX_PIECES 10
/**@}*/

/**
 * @fn void init_data (struct s_data* data, int* argc, char** argv, bool (*game_over)(cgame))
 * @brief Wrapper provided to initialize fields of a s_data struct type.
 * @param[in,out] data A pointer to the structure that will be initialized.
 * @param[in] argc A pointer the argcount of the program.
 * @param[in] argv A pointer to an array containing the arguments of the program.
 * @param[in] game_over A pointer to the function that will decide when the game is over.
 * @pre data must be a pointer to an area located on the stack, not in the heap.
 */
void init_data(struct s_data* data, int* argc, char** argv, bool (*game_over)(cgame));

/**
 * @fn void delete_data (struct s_data* data)
 * @brief Wrapper called to unallocate fiels of a s_data struct type.
 * @param[in,out] data A pointer to the structure that will be cleared properly.
 * @pre data must not be a pointer to an area located on the stack, not in the heap.
 * @post data->status field will be set to END_STEP at the end of the process.
 */
void delete_data(struct s_data* data);

#endif /* _DATA_H */
