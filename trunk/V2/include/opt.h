#ifndef _OPT_H
# define _OPT_H

/**
 * @file opt.h
 * @brief Header associated with input options flags and wrappers.
 */

#ifndef _FLAGS
# define _FLAGS
/**
 * @def NB_FLAGS 5 The number of special input flags in the program
 */
# define NB_FLAGS 5
/**
 * @addtogroup INPUT_MACROS
 * @brief Macros associated with potential input flags, such as terminal mode or solver mode.
 * @{
 */
# define TERM_FLAG 0
# define GUI_FLAG 1
# define IOCTL_FLAG 2
# define SOLVER_FLAG 3
# define FILE_FLAG 4
/**@}*/
#endif /* _FLAGS */

/**
 * @fn int is_opt (const char* s)
 * @brief Wrapper checking if the input string in a flag or not.
 * @param[in] s The string on which the check will be performed.
 * @return true if s[0] equals '-' s is two bytes long, false otherwise.
 */
int is_opt(const char* s);

/**
 * @fn void parse_opt (struct s_data* data)
 * @brief Wrapper called to parse the option detected at index position of argv.
 * @param[in,out] data The field containing needed data and field to set if an error happen.
 */
void parse_opt(struct s_data* data);

#endif /* _OPT_H */
