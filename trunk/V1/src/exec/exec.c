#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include <exec>


#ifndef _GAME_S
# define _GAME_S
struct game_s {
  int board[6][6];
  int nbMove;
  piece* piece;
  int nbPiece;
  piece redCar;
} __attribute__((packed));
#endif /* _GAME_S */


#define TERM_F 0
#define GUI_F 1
#define IOCTL_F 2
#define SOLVER_F 3
#define FILE_F 4


static inline int is_opt(const char* str);
static void parse_opt(const char* opt, int* flags);

static int parse_game_data(const char* filepath, game* g_ptr);
static void get_piece(char* line, piece* dst);

static void printout_game(const struct s_exec* data_set);
static void print_buffer(const char* buffer);
static void print_full_board_line(char* buffer);
static void print_empty_board_line(char* buffer);
static void print_line(const int n, int** grid, char* buffer);

static void prompt_user(struct s_exec* data_set);
static void manage_piece(char* buffer, struct s_exec* data_set);
static void manage_move(const int nb_pc, char* buffer, struct s_exec* data_set);

static int is_dir(const char* buffer);
static dir get_dir(const char* buffer);

static inline void clear_tab(int** tab);

static void actualise_tab(struct s_exec* data_set);

static inline void xfree(char** ptr)
{
  if (*ptr != NULL)
    { free(*ptr); *ptr = NULL; }
}

void init_exec(struct s_exec* data_set, const int argc, const char** argv)
{
  (*data_set).status = 0;
  (*data_set).flags = 0;
  for (int i = 1; i < argc && (*data_set).flags >= 0; ++i)
    {
      if (is_opt(*(argv + i)))
	parse_opt(*(argv + i), &((*data_set).flags));
    }
  (*data_set).flags = (((*data_set).flags & (1 << GUI_F)) && ((*data_set).flags & (1 << TERM_F))) ? -1 : (*data_set).flags;
  (*data_set).g = NULL;
  if (argc > 1 && !is_opt(*(argv + argc - 1)))
    (*data_set).status = parse_game_data(*(argv + argc - 1), &((*data_set).g));
  (*data_set).board = malloc(sizeof(*((*data_set).board)) * 6);
  for (int j = 0; j < 6; ++j)
    (*data_set).board[j] = malloc(sizeof(*((*data_set).board[j])) * 6);  
  actualise_tab(data_set);
}

static inline int
is_opt(const char* str)
{ return ((strlen(str) == 2) && (*str == '-'))?1:0; }

static void parse_opt(const char* opt, int* flags)
{
  switch (*(opt + 1))
    {
    case 't' :
      *flags |= (1 << TERM_F);
      break;
    case 'g' :
      *flags |=	(1 << GUI_F);
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
    }
}

static int parse_game_data(const char* filepath, game* g_ptr)
{
  if (filepath == NULL)
    return -1;
  FILE* fstream = fopen(filepath, "r");
  if (fstream != NULL)
    {
      char buffer[16];
      char* str = buffer;
      piece* pcs = malloc(sizeof(*pcs) * 19);
      int nb_pcs = 0;
      for (int i = 0; (i < 18) && (str != NULL); ++i)
	{
	  str = fgets(buffer, 15, fstream);
	  if (str != NULL)
	    {
	      get_piece(str, &(*(pcs + i)));
	      ++nb_pcs;
	      *(pcs + nb_pcs) = NULL; 
	    }
	}
      *g_ptr = new_game_hr(nb_pcs, pcs);
      return fclose(fstream);
    }
  return -1;
}

static void get_piece(char* line, piece* dst)
{
  int x, y;
  bool small;
  bool horizontal;
  char* token = NULL;
  x = atoi(strtok(line, ", "));
  y = atoi(strtok(NULL, ", "));
  token = strtok(NULL, ", ");
  small = (*token == 's') ? true : false;
  token = strtok(NULL, ", ");
  *(token + strlen(token) - 1) = '\0';
  horizontal = (*token == 'h') ? true : false;
  *dst = new_piece_rh(x, y, small, horizontal);
}

static void printout_game(const struct s_exec* data_set)
{
  char* buffer = malloc(sizeof(*buffer) * 38);
  *(buffer + 37) = '\0';
  fwrite("\n", 1, 1, stdout);
  print_full_board_line(buffer);
  for (int i = 0; i < 6; ++i)
    {
      print_empty_board_line(buffer);
      print_line(i, (*data_set).board, buffer);
      print_empty_board_line(buffer);
      print_full_board_line(buffer);
    }
  xfree(&buffer);
}

static void print_buffer(const char* buffer)
{ fwrite(buffer, 37, 1, stdout); fwrite("\n", 1, 1, stdout); }

static void print_full_board_line(char* buffer)
{
  for (int i = 0; i < 37; ++i)
    *(buffer + i) = '*';
  print_buffer(buffer);
}

static void print_empty_board_line(char* buffer)
{
  for (int i = 0; i < 6; ++i)
    {
      *(buffer + (i * 6)) = '*';
      *(buffer + (i * 6) + 1) = ' ';
      *(buffer + (i * 6) + 2) = ' ';
      *(buffer + (i * 6) + 3) = ' ';
      *(buffer + (i * 6) + 4) = ' ';
      *(buffer + (i * 6) + 5) = ' ';
    }
  print_buffer(buffer);
}

static void print_line(const int n, int** grid, char* buffer)
{
  for (int i = 0; i < 6; ++i)
    {
      *(buffer + 6 * i) = '*';
      *(buffer + 6 * i + 1) = ' ';
      *(buffer + 6 * i + 2) = ' ';
      if (grid[n][i] >= 0)
	*(buffer + 6 * i + 3) = '0' + grid[n][i];
      else
	*(buffer + 6 * i + 3) = ' ';
      *(buffer + 6 * i + 4) = ' ';
      *(buffer + 6 * i + 5) = ' ';
    }
  print_buffer(buffer);
}

void loop_exec(struct s_exec* data_set)
{
  printout_game(data_set);
  if ((*data_set).status == 0)
    prompt_user(data_set);
  if ((*data_set).status == 0)
    (*data_set).status = (game_over_hr((*data_set).g) == true) ? 1 : 0;
  if ((*data_set).status == 0)
    actualise_tab(data_set);
}

void end_exec(struct s_exec* data_set) { delete_game((*data_set).g); }

static void prompt_user(struct s_exec* data_set)
{
  char* buffer = malloc(sizeof(*buffer) * 32);
  manage_piece((char*) buffer, data_set);
  free(buffer);
}

static void manage_piece(char* buffer, struct s_exec* data_set)
{
  char* buff_ret = NULL;
  fprintf(stdout, "Choose the number of the piece to move. ");
  buff_ret = fgets(buffer, 31, stdin);
  if (buff_ret == NULL || (strlen(buff_ret) != 2))
    (*data_set).status = -1;
  else
    {
      *(buffer + 1) = '\0';
      int nb_pc = atoi(buffer);
      if (nb_pc < game_nb_pieces((*data_set).g) && nb_pc >= 0)
	manage_move(nb_pc, buffer, data_set);
      else
	{
	  fprintf(stderr, "invalid piece number provided\n");
	  manage_piece(buffer, data_set);
	}
    }
}

static void manage_move(const int nb_pc, char* buffer, struct s_exec* data_set)
{
  char* buff_ret = NULL;
  fprintf(stdout, "Choose a direction to move the piece. ");
  buff_ret = fgets(buffer, 31, stdin);
  if (buff_ret == NULL)
    (*data_set).status = -1;
  else
    {
      int l = strlen(buffer);
      if (l >= 3 && l <= 6)
	{
	  *(buffer + strlen(buffer) - 1) = '\0';
	  if (is_dir(buffer))
	    {
	      dir mv = get_dir(buffer);
	      if (play_move((*data_set).g, nb_pc, mv, 1) == false)
		(*data_set).status = 1;
	    }
	  else
	    (*data_set).status = 1;
	}
      else
	(*data_set).status = 1;
      if ((*data_set).status == 1)
	{
	  (*data_set).status = 0;
	  fprintf(stderr, "invalid direction provided for movement\n");
	  manage_move(nb_pc, buffer, data_set);
	}
    }
}

static int is_dir(const char* buffer)
{
  switch (strlen(buffer))
    {
    case 2 :
      return (strcmp(buffer, "UP") == 0) ? 1 : 0;
    case 4 :
      return (strcmp(buffer, "DOWN") == 0 || strcmp(buffer, "LEFT") == 0) ? 1 : 0;
    case 5 :
      return (strcmp(buffer, "RIGHT") == 0) ? 1 : 0;
    default :
      return 0;
    }
  return 0;
}

static dir get_dir(const char* buffer)
{
  if (strlen(buffer) == 2)
    return UP;
  if (strlen(buffer) == 5)
    return RIGHT;
  if (strcmp(buffer, "DOWN") == 0)
    return DOWN;
  return LEFT;
}

static inline void
clear_tab(int** tab)
{
  for (int i = 0; i < 6; ++i)
    {
      for (int j = 0; j < 6; ++j)
	tab[i][j] = -1;
    }
}

static void
actualise_tab(struct s_exec* data_set)
{
  clear_tab((*data_set).board);
  for (int i = 0; i < game_nb_pieces((cgame) (*data_set).g); ++i)
    {
      cpiece cpc = game_piece((cgame) (*data_set).g, i);
      int x = get_x(cpc); int y = get_y(cpc);
      int dim = 0;
      if (is_horizontal(cpc))
	{
	  dim = get_width(cpc);
	  for (int j = 0; j < dim; ++j)
	    (*data_set).board[y][x + j] = i;
	}
      else
	{
	  dim = get_height(cpc);
	for (int j = 0; j < dim; ++j)
	  (*data_set).board[y + j][x] = i;
	}
    }
}
