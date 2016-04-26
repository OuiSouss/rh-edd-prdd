#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <data>
#include <error_flags>
#include <opt>

/**
 * This function is declared here is it should never be called
 * from another place.
 */
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

/**
 * @fn static inline int get_flag (const int f, const int* flags)
 * @brief Local function used to know if a flag is set or not.
 * @param[in] f The position of the flag.
 * @param[in] flags The array containing the flags values.
 * @return 0 if the flag is not set, 1 otherwise.
 */
static inline int get_flag(const int f, const int* flags)
{ return flags[f]; }

/**
 * @fn static inline void set_flag (const int f, int* flags)
 * @brief Local function used to set a flag.
 * @param[in] f The flag to set.
 * @param[in,out] flags The array containing all the flags.
 */
static inline void set_flag(const int f, int* flags)
{ flags[f] = 1; }

/**
 * @fn static inline void set_width (struct s_data* data)
 * @brief Local function used to set the width of the new game.
 * @param[in,out] data The structure containing needed data.
 */
static inline void set_width(struct s_data* data)
{
  if (data->width != -1)
    data->status = MULTIPLE_SIZE_ERROR;
  else
    data->width = get_grid_size(data);
}

/**
 * @fn static inline void set_height (struct s_data* data)
 * @brief Local call used to set the height of the new game.
 * @param[in,out] data The structure containing needed data.
 */
static inline void set_height(struct s_data* data)
{
  if (data->height != -1)
    data->status = MULTIPLE_SIZE_ERROR;
  else
    data->height = get_grid_size(data);
}

/**
 * @fn static int get_grid_size (struct s_data* data)
 * @brief Local generic call used to parse either a width or a height as input.
 * @parap[in] data The structure containing needed data.
 * @return The size converted to an integer.
 */
static int get_grid_size(struct s_data* data)
{
  int size = 0;
  ++(data->index);
  for (int i = 0; (i < (int)strlen(data->av[data->index])) && (data->status > END_STEP); ++i)
    {
      if (!isdigit(data->av[data->index][i]))
	data->status = OPT_ERROR;
    }
  if (data->status > END_STEP)
    size = atoi(data->av[data->index]);
  return size;
}
