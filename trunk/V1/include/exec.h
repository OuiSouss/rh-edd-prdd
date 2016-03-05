#ifndef _EXEC_H
# define _EXEC_H

# include <game.h>

struct s_exec
{
  int status;
  int flags;
  game g;
};

void init_exec(struct s_exec* data_set, const int argc, const char** argv);

#endif /* _EXEC_H */
