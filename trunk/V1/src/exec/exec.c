#include <string.h>

#include <exec>

static inline int is_opt(const char* str);
static void parse_opt(const char* opt, int* flags);

void init_exec(struct s_exec* data_set, const int argc, const char** argv)
{
  (*data_set).status = 1;
  (*data_set).flags = 0;
  for (int i = 1; i < argc - 1 && (*data_set).flags >= 0; ++i)
    {
      if (is_opt(*argv + i))
	parse_opt(*argv + i, &((*data_set).flags));
    }
}

static inline int
is_opt(const char* str)
{ return ((strlen(str) == 2) && (*str == '-'))?1:0; }

#define TERM_F 0
#define GUI_F 0
#define IOCTL_F 1
#define SOLVER_F 2
#define FILE_F 3

static void parse_opt(const char* opt, int* flags)
{
  switch (*opt + 1)
    {
    case 't' :
      *flags &= (0 << TERM_F);
      break;
    case 'g' :
      *flags |= (1 << GUI_F);
      break;
    case 'i' :
      *flags |= (1 << IOCTL_F);
      break;
    case 's' :
      *flags |= (1 << SOLVER_F);
      break;
    case 'f' :
      *flags |= (1 << FILE_F);
      break;
    default :
      *flags = -1;
    }
}
