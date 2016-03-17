#include <stdio.h>
#include <string.h>

#include <data>

#ifndef _ERRORS
# define _ERRORS

# define ALLOC_ERROR -1
# define OPT_ERROR -2
# define TERM_GUI_ERROR -3
# define IOCTL_TERM_ERROR -4
# define SOLVER_GAME_ERROR -5
# define FILE_INPUT_ERROR -6
# define FILE_ACCESS_ERROR -7

#endif /* _ERRORS */

#ifndef _FLAGS
# define _FLAGS

# define TERM_FLAG 0
# define GUI_FLAG 1
# define IOCTL_FLAG 2
# define SOLVER_FLAG 3
# define FILE_FLAG 4

#endif /* _FLAGS */

#define BUFFER_SIZE 16
#define MAX_PIECES 9


static inline int get_flag(const int f, const int* flags);
static inline void set_flag(const int f, int* flags);

static void parse_input_file(struct s_data* data, const int n);
static void parse_piece(struct s_data* data, const char* s);

static void parse_token(void* ptr, char* s, struct s_data* data);
static inline void get_int(void** ptr, char* s);
static inline void get_bool(void** ptr, char* s);


int is_opt(const char* s)
{ return (s && (strlen(s) == 2) && *s == '-'); }

void parse_opt(struct s_data* data, const int n)
{
  switch (data->argv[n][1])
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
      if (n >= (data->argc - 1))
	data->status = FILE_INPUT_ERROR;
      else
	data->index = n + 1;
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

static void parse_input_file(struct s_data* data)
{
  FILE* fstream = fopen(data->argv[data->index], "r");
  if (fstream == NULL)
    data->status = FILE_ACCESS_ERROR;
  if (data->status >= 0)
    {
      data->pcs = malloc(sizeof(*pcs) * MAX_PIECES);
      if (data->pcs == NULL)
	data->status = ALLOC_ERROR;
      char buffer[BUFFER_SIZE];
      char* line = buffer;
      for (int i = 0; (data->status >= 0) && (i < MAX_PIECES) && (line != NULL); ++i)
	{
	  line = fgets(buffer, BUFFER_SIZE - 1, fstream);
	  parse_piece(line, data);
	}
      fclose(fstream);
    }
}


static void parse_piece(struct s_data* data, char* s)
{
  int x, y;
  int w, h;
  bool move_x, move_y;
  char* token = NULL;

  token = strtok(line, ", ");
  parse_token(&x, token, ", ", data);
  token = strtok(NULL, ", ");
  parse_token(&y, token, ", ", data);
  token = strtok(NULL, ", ");
  parse_token(&w, token, ", ", data);
  token = strtok(NULL, ", ");
  parse_token(&h, token, ", ", data);
  token = strtok(NULL, ", ");
  parse_token(&move_x, token, ", ", data);
  token = strtok(NULL, ", ");
  parse_token(&move_y, token, ", ", data);
}

static void parse_token(void* ptr, char* s, struct s_data* data)
{
  static int step = 0;
 // typedef void (*get_token)(void**, char*, struct s_data*);
  void (*get_token[])(void**, char*, struct s_data*) = {get_int, get_int, get_int, get_int, get_bool, get_bool};
  if (data->status > 0)
    {
      switch (step < 6)
	{
	case true :
	  process[step++](&ptr, s);
	  break;
	default :
	  step = 0;
	}
      if (!ptr)
	data->status = OPT_ERROR;
    }
}

static inline void
get_int(void** ptr, char* s)
{ **(int**)ptr = atoi(s); }

static inline void
get_bool(void** ptr, char* s)
{ **(bool**)ptr = strcmp(s, "true"); }
