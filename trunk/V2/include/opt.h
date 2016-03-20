#ifndef _OPT_H
# define _OPT_H

#ifndef _FLAGS
# define _FLAGS

# define NB_FLAGS 5

# define TERM_FLAG 0
# define GUI_FLAG 1
# define IOCTL_FLAG 2
# define SOLVER_FLAG 3
# define FILE_FLAG 4

#endif /* _FLAGS */

int is_opt(const char* s);
void parse_opt(struct s_data* data);

#endif /* _OPT_H */
