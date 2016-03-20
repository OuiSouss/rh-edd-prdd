#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include <data>
#include <error_flags>
#include <xfunc>


#define LINE_SIZE 17


static void parse_piece(struct s_data* data, char* s);
static void parse_token(void* ptr, char* s);
static inline void get_int(void** ptr, char* s);
static inline void get_bool(void** ptr, char* s);


void parse_input_file(struct s_data* data)
{
  ++(data->index);
  FILE* fstream = fopen(data->av[data->index], "r");
  if (fstream == NULL)
    data->status = FILE_ACCESS_ERROR;
  if (data->status > END_STEP)
    {
      data->pcs = xmalloc((sizeof(*(data->pcs)) * MAX_PIECES), &(data->status));
      char buffer[BUFFER_SIZE];
      char* line = buffer;
      for (int i = 0; (data->status > END_STEP) && (i < MAX_PIECES) && (line != NULL); ++i)
	{
	  line = fgets(buffer, BUFFER_SIZE - 1, fstream);
	  if (line && (strlen(line) == LINE_SIZE))
	    parse_piece(data, line);
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

  token = strtok(s, ", ");
  parse_token(&x, token);
  token = strtok(NULL, ", ");
  parse_token(&y, token);
  token = strtok(NULL, ", ");
  parse_token(&w, token);
  token = strtok(NULL, ", ");
  parse_token(&h, token);
  token = strtok(NULL, ", ");
  parse_token(&move_x, token);
  token = strtok(NULL, ", ");
  parse_token(&move_y, token);
  fprintf(stdout, "\n\n\n x='%d', y='%d', w='%d', h='%d'", x, y, w, h);
  if (move_x == true)
    fprintf(stdout, ", move_x = true");
  else
    fprintf(stdout, ", move_x = false");
  if (move_y == true)
    fprintf(stdout, ", move_y = true");
  else
    fprintf(stdout, ", move_y = false");
  data->pcs[(data->nb_pcs)++] = new_piece(x, y, w, h, move_x, move_y);
}

static void parse_token(void* ptr, char* s)
{
  static int step = 0;
  void (*get_token[])(void**, char*) = {get_int, get_int, get_int, get_int, get_bool, get_bool};
  if (step < 6)
    get_token[step++](&ptr, s);
  else
    step = 0;
}

static inline void
get_int(void** ptr, char* s)
{ **(int**)ptr = atoi(s); }

static inline void
get_bool(void** ptr, char* s)
{
  if (s[0] == '1')
    **((bool**) ptr) = true;
  else
    **((bool**) ptr) = false;
}
