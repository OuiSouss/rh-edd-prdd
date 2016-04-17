#include "game.h"
#include "piece.h"
#include "list.h"

#include <stdbool.h>
#include <stdio.h>

#define EXIT_LINE_RH 3
/**
 * @pre length of line_exit need to be equals to the width of the game g
 **/

void piece_on_line_exit(game g, int* line_exit)
{
  int width = game_width(g);
  for(int i=0; i<width; ++i)
  {
    line_exit[i] = game_square_piece(g, i, EXIT_LINE_RH);
  }
}

bool is_marked(bool *t, int piece_num)
{
  return t[piece_num];
}

bool* mark_piece(int piece_num, bool* tab_marked)
{
  tab_marked[piece_num] = true;
  return tab_marked;
}

bool* unmark_piece(int piece_num, bool* tab_marked)
{
  tab_marked[piece_num] = false;
  return tab_marked;
}

int search_nearest_exit(int* line_exit, int width)
{
  int i = 0;
  int nb_piece_nearest_exit = 0;
  while(i<width)
  {
    if(line_exit[i]!=0 && line_exit[i]!=-1)
      nb_piece_nearest_exit = line_exit[i];
    ++i;
  }
  return nb_piece_nearest_exit;
}

int number_free_spaces(cgame g)
{
  int free_spaces = 0;
  int width = game_width(g);
  int height = game_height(g);
  for(int j=0; j<height; ++j)
    for(int i=0; i<width; ++i)
      if(game_square_piece((game)g,i,j)==-1)
	free_spaces+=1;
  return free_spaces;
}

int solve_rush_hour(cgame g)
{
  if (number_free_spaces(g)==0)
    return -1;
  int width = game_width(g);
  int height = game_height(g);
  int nb_pieces = game_nb_pieces(g);
  game copy_g = new_game(width,height,nb_pieces,NULL);
  copy_game(g,copy_g);
  int line_exit[width];
  piece_on_line_exit(copy_g,line_exit);
  
  while (!game_over_hr(copy_g))
  {
    int current_p = search_nearest_exit(line_exit,width);
  }
  return 0;
}
