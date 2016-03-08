#ifndef _EXEC_H
# define _EXEC_H

# include <game.h>


# ifndef _S_EXEC
#  define _S_EXEC
/**
 * @struct s_exec
 * @brief The structure used to handle data related to execution.
 */
struct s_exec
{
  int status;	/*!< The variable used to track current program state. */
  int flags;	/*!< The variable used to track input mode chosen by the user */
  game g;	/*!< A pointer to the kind of structure used to store game data */
  int** board;
};
# endif /* _S_EXEC */

/**
 * @fn void init_exec (struct s_exec* data_set, const int argc, const char** argv)
 * @brief Wrapper called by the program to set execution context.
 * @param[in, out] data_set A pointer to the structure handling our data.
 * @param[in] argc the number of arguments given to the program.
 * @param[in] argv the array of arguments given as input for the program.
 */
void init_exec(struct s_exec* data_set, const int argc, const char** argv);

/**
 * @fn void loop_exec (struct s_exec* data_set)
 * @brief Wrapper called for handling the whole execution.
 * @param[in, out] data_set A pointer to the program data.
 */
void loop_exec(struct s_exec* data_set);

/**
 * @fn void end_exec (struct s_exec* data_set)
 * @brief Wrapper handling the end of the program.
 * @param[in, out] data_set A pointer on the target to clean.
 */
void end_exec(struct s_exec* data_set);

#endif /* _EXEC_H */
