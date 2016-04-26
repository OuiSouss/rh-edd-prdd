#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <data>
#include <error_flags>
#include <xfunc>

/**
 * @def LINE_SIZE 17 Local macro used to track the exact
 * size each line of the input file should have (excluding
 * the last one).
 */
#define LINE_SIZE 17

static void parse_piece(struct s_data* data, char* s);
static void parse_token(void* ptr, char* s);
static inline void get_int(void** ptr, char* s);
static inline void get_bool(void** ptr, char* s);

/**
 * @fn void parse_input_file (struct s_data* data)
 * @brief Function encapsulating the parsing of an input
 * config file.
 * @param[in,out] data The field containing the path to
 * the input file and where to store parsed data.
 */
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
      for (int i = 0; (data->status > END_STEP) && (line != NULL) && (i < MAX_PIECES); ++i)
	{
	  line = fgets(buffer, BUFFER_SIZE - 1, fstream);
	  if (line && (strlen(line) == LINE_SIZE))
	    parse_piece(data, line);
	  else
	    line = NULL;
	}
      fclose(fstream);
    }
}

/**
 * @fn static void parse_piece (struct s_data* data, char* s)
 * @brief Function encapsulating the parsing of a piece.
 * @param[in,out] data The structure where to store parsed data.
 * @param[in] s The array associated with the line to parse.
 */
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
  data->pcs[(data->nb_pcs)++] = new_piece(x, y, w, h, move_x, move_y);
}

/**
 * @fn static void parse_token (void* ptr, char* s)
 * @brief The local function used to a specific data of piece.
 * @param[in,out] ptr A pointer to where store the parsed data.
 * @param[in] s The array containing the data to parse.
 */
static void parse_token(void* ptr, char* s)
{
  static int step = 0;
  void (*get_token[])(void**, char*) = {get_int, get_int, get_int, get_int, get_bool, get_bool};
  if (step < 6)
    get_token[step++](&ptr, s);
  else
    step = 0;
}

/**
 * @fn static inline void get_int (void** ptr, char* s)
 * @brief Wrapper used to parse an int input data.
 * @param[in,out] ptr A pointer pointing to the pointer pointing where parse data will be stored.
 * @param[in] s The array containing needed data as a string.
 */
static inline void get_int(void** ptr, char* s)
{ **(int**)ptr = atoi(s); }


/**
 * @fn static inline void get_bool (void** ptr, char* s)
 * @brief Local wrapper used to parse an input bool type.
 * @param[in,out] ptr A pointer to a pointer on the field used to store the data.
 * @param[in] s The array containing input data as a string.
 */
static inline void get_bool(void** ptr, char* s)
{
  if (s[0] == '1')
    **((bool**) ptr) = true;
  else
    **((bool**) ptr) = false;
}
