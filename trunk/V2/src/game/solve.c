#include "game.h"
#include "piece.h"
#include "list.h"
#include <stdio.h>
#include <stdlib.h>

#define EXIT_LINE_RH 3

/**
 * @brief Permit to have the line where red car exit for a rush hour game
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

/**
 * @return true if the piece at position piece_num in t is marked
 **/
bool is_marked(bool *t, int piece_num)
{
  return t[piece_num];
}

/**
 * @brief Permit to mark a piece at position piece_num in the board array_marked
 **/
void mark_piece(int piece_num, bool* array_marked)
{
  array_marked[piece_num] = true;
}

/**
 * @brief Permit to unmark a piece at position piece_num in the board array_marked
**/
void unmark_piece(int piece_num, bool* array_marked)
{
  array_marked[piece_num] = false;
}

/**
 * @brief Search the number of a piece that bloked the exit of red car
 * @return the number of piece that is the nearest of the exit
 **/
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

/**
 * @return number of free space of the game in parameter
 **/
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

/**
 * @brief fonction which have the role to solve a game but it doesn't work
 * @return number of move we done to solve game
 **/
int solve_rush_hour(game g)
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
    cpiece current_piece = game_piece(g,current_p);
  }
  return game_nb_moves((cgame)copy_g);
}

int main(int argc, char* argv[])
{
  if (argc==3)
  {
    if (*argv[1]=='r')
    {
      FILE* file_solve = fopen(argv[2],"r");
      if(file_solve==NULL)
      {
	fprintf(stderr, "Problem in openning file in argument\n");
	return EXIT_FAILURE;
      }
      int width,height,nb_pieces = 0;
      int x,y,p_width,p_height,move_x,move_y = 0;
      piece *pieces;
      
      while(!feof(file_solve))
      {
	if(fscanf(file_solve,"%d %d",&width,&height) != 2)
	  fprintf(stderr, "Fsanf problem on first line\n");
	if(fscanf(file_solve,"%d",&nb_pieces)!=1)
	  fprintf(stderr, "Fsanf problem on second line\n");
	pieces = malloc(sizeof(*pieces)*nb_pieces);
	if (pieces==NULL)
	{
	  fprintf(stderr,"Allocation problem\n");
	  exit(EXIT_FAILURE);
	}
	int cmp = 0;
	while(!feof(file_solve))
	{
	  if(fscanf(file_solve,"%d %d %d %d %d %d", &x,&y,&p_width,&p_height,&move_x,&move_y)!=6)
	    fprintf(stderr, "Fsanf problem on line\n");
	  pieces[cmp] = new_piece(x,y,p_width,p_height,move_x,move_y);
	}
      }
      game g = new_game(width,height,nb_pieces,pieces);
      solve_rush_hour(g);
      fprintf(stdout, "Ceci est la mauvaise réponse, suite à un manque d'organisation le solveur n'est pas fini");

      fclose(file_solve);
    }
    else
      printf("Nous sommes vraiment désolés mais notre algorithme ne fonctionne vraiment pas pour un ane rouge. Déjà, il faudrait qu'il fonctionne pour le rush hour!!!!!!!!!!!!!!!!!!!!!!!!!\n");
  }
  else
    fprintf(stderr, "Arguments are probably false: ./solveur  'a or r' config.txt\n");
}
