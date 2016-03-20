#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include <data>
#include <error_flags>
#include <opt>


void parse_input_file(struct s_data* data);


static inline int get_flag(const int f, const int* flags);
static inline void set_flag(const int f, int* flags);

static inline void set_width(struct s_data* data);
static inline void set_height(struct s_data* data);

static inline int get_grid_size(struct s_data* data);


int is_opt(const char* s)
{ return (s && (strlen(s) == 2) && *s == '-'); }

void parse_opt(struct s_data* data)
{
  switch (data->av[data->index][1])
    {
    case 't' :
      if (get_flag(GUI_FLAG, data->flags))
	data->status = TERM_GUI_ERROR;
      else
	set_flag(TERM_FLAG, data->flags);
      break;
    case 'g' :
      if (get_flag(TERM_FLAG, data->flags))
	data->status = TERM_GUI_ERROR;
      else
	set_flag(GUI_FLAG, data->flags);
      break;
    case 'i' :
      if (get_flag(TERM_FLAG, data->flags))
	set_flag(IOCTL_FLAG, data->flags);
      else
	data->status = IOCTL_TERM_ERROR;
      break;
    case 's' :
      if (get_flag(TERM_FLAG, data->flags) || get_flag(GUI_FLAG, data->flags))
	data->status = SOLVER_GAME_ERROR;
      else
	set_flag(SOLVER_FLAG, data->flags);
      break;
    case 'f' :
      if (data->index >= (data->ac - 1))
	data->status = FILE_INPUT_ERROR;
      else
	parse_input_file(data);
      break;
    case 'w' :
      set_width(data);
      break;
    case 'h' :
      set_height(data);
      break;
    default :
      data->status = OPT_ERROR;
    }
}

static inline int
get_flag(const int f, const int* flags)
{ return flags[f]; }

static inline void
set_flag(const int f, int* flags)
{ flags[f] = 1; }

static inline void
set_width(struct s_data* data)
{
  if (data->width != -1)
    data->status = MULTIPLE_SIZE_ERROR;
  else
    data->width = get_grid_size(data);
}

static inline void
set_height(struct s_data* data)
{
  if (data->height != -1)
    data->status = MULTIPLE_SIZE_ERROR;
  else
    data->height = get_grid_size(data);
}

static inline int
get_grid_size(struct s_data* data)
{
  int size = 0;
  ++(data->index);
  for (int i = 0; (i < (int)strlen(data->av[data->index])) && (data->status > END_STATUS); ++i)
    {
      if (!isdigit(data->av[data->index][i]))
	data->status = OPT_ERROR;
    }
  if (data->status > END_STATUS)
    size = atoi(data->av[data->index]);
  return size;
}
