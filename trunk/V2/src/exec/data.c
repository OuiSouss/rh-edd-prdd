#include <stdlib.h>

#include <piece.h>
#include <game.h>

#include <data>
#include <opt>
#include <xfunc>


void init_data(struct s_data* data, int *argc, char** argv, bool (*game_over)(cgame))
{
  data->ac = *argc;
  data->av = argv;
  data->status = START_STATUS;
  data->flags = xmalloc(sizeof(*(data->flags)) * NB_FLAGS, &(data->status));
  data->index = 1;
  data->width = -1;
  data->height = -1;
  data->pcs = NULL;
  data->nb_pcs = 0;
  data->g = NULL;
  data->game_over = game_over;
}

void delete_data(struct s_data* data)
{
  xfree((void**) &(data->flags));
  delete_game(data->g);
  for (;data->nb_pcs > 0;)
    delete_piece(data->pcs[--(data->nb_pcs)]);
  xfree((void**) &(data->pcs));
  data->status = END_STATUS;
}
