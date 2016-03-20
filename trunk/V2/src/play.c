#include <stdio.h>
#include <stdlib.h>


#include <data>


int is_opt(const char* s);
void parse_opt(struct s_data* data);

void manage_error(struct s_data* data);

void printout_game(struct s_data* data);

void manage_move(struct s_data* data);


static bool game_over_ar(cgame g);
static void parse_argv(struct s_data* data);

static void game_loop(struct s_data* data);



int main(int argc, char** argv)
{
  struct s_data data;
  bool (*game_over)(cgame);
#ifdef _RUSH_HOUR
# define _GAME_HR
  game_over = &game_over_hr;
#endif /* _GAME_HR */
#ifndef _RUSH_HOUR
# define _GAME
  game_over = &game_over_ar;
#endif /* _GAME */
  init_data(&data, &argc, argv, game_over);
  parse_argv(&data);
  while (data.status > END_STEP)
    game_loop(&data);
  if (data.status < END_STEP)
    manage_error(&data);
  delete_data(&data);
  return data.status;
}

static bool game_over_ar(cgame g)
{
  cpiece ar = game_piece(g, 0);
  return ((get_y(ar) + get_height(ar) - game_height(g)) == 0);
}

static void parse_argv(struct s_data* data)
{
  while((data->status == START_STEP) && (data->index < data->ac))
    {
      if (is_opt(data->av[data->index]))
	parse_opt(data);
      ++(data->index);
    }
  if (data->status == START_STEP)
    {
      if (data->width == -1)
	data->width = 6;
      if (data->height == -1)
	data->height = 6;
    }
}

static void game_loop(struct s_data* data)
{
  switch (data->status)
    {
    case START_STEP :
      data->g = new_game(data->width, data->height, data->nb_pcs, data->pcs);
      data->status = LOOP_STEP;
      break;
    case LOOP_STEP :
      if (data->game_over(data->g))
	{
	  

	}
      else
	{
	  printout_game(data);
	  manage_move(data);
	}
      break;
    case INPUT_ERROR_STEP :
      fprintf(stderr, "\nunknown keyboard entry\n");
      data->status = END_STEP;
      break;
    }
}
