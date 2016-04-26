#ifndef _ERROR_FLAGS_H
# define _ERROR_FLAGS_H

/**
 * @file error_flags.h
 * @brief file containing error codes for the program.
 */

/**
 * @addtogroup ERROR_MACROS
 * @brief Macros associated with critical errors that will cause the program to end.
 * @{
 */
# define ALLOC_ERROR -1
# define WRONG_USAGE_ERROR -2
# define OPT_ERROR -3
# define TERM_GUI_ERROR -4
# define IOCTL_TERM_ERROR -5
# define SOLVER_GAME_ERROR -6
# define FILE_INPUT_ERROR -7
# define FILE_ACCESS_ERROR -8
# define MULTIPLE_SIZE_ERROR -9
/**@}*/

#endif /* _ERROR_FLAGS_H */
