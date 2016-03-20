#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <data>
#include <xfunc>

static void manage_piece(struct s_data* data, char* buffer);
static void manage_dir(struct s_data* data, const int nb_pc, char* buffer);
static int is_dir(const char* buffer);
static dir get_dir(const char* buffer);


void manage_move(struct s_data* data)
{
  char* buffer = xmalloc((sizeof(*buffer) * BUFFER_SIZE), &(data->status));
  manage_piece(data, buffer);
  xfree((void**) &buffer);
}

static void manage_piece(struct s_data* data, char* buffer)
{
  char* buff_ret = NULL;
  fprintf(stdout, "Choose the number of the piece to move : ");
  buff_ret = fgets(buffer, BUFFER_SIZE - 1, stdin);
  if (buff_ret == NULL)
    data->status = INPUT_ERROR_STEP;
  else
    {
      data->status = PIECE_STEP;
      buffer[1] = '\0';
      int nb_pc = atoi(buffer);
      if (nb_pc < game_nb_pieces(data->g) && nb_pc >= 0)
	manage_dir(data, nb_pc, buffer);
      else
	{
	  fprintf(stderr, "\ninvalid piece number provided\n");
	  data->status = LOOP_STEP;
	}
    }
}

static void manage_dir(struct s_data* data, const int nb_pc, char* buffer)
{
  char* buff_ret = NULL;
  fprintf(stdout, "Choose a direction to move the piece : ");
  buff_ret = fgets(buffer, 31, stdin);
  if (buff_ret == NULL)
    data->status = INPUT_ERROR_STEP;
  else
    {
      data->status = MOVE_STEP;
      int l = strlen(buffer);
      if (l >= 3 && l <= 6)
	{
	  buffer[strlen(buffer) - 1] = '\0';
	  if (is_dir(buffer))
	    {
	      dir mv = get_dir(buffer);
	      if (play_move(data->g, nb_pc, mv, 1) == false)
		fprintf(stderr, "invalid direction provided for movement\n");
	    }
	  else
	    fprintf(stderr, "unrecongnised direction provided for movement\n");
	}
      data->status = LOOP_STEP;
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
