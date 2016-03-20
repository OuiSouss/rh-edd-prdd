#include "game.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

struct game_s
{
     int** board;
     int width;
     int height;
     int nb_move;
     piece* piece;
     int nb_piece;
};


/**
 * In this Version, we are doing the hypothesis that the
 * piece 0 is in *piece and this is the piece which is going to exit.
 * So, we are in need doing the test if the first piece is present.
 *
 *
 **/
game new_game (int width, int height, int nb_pieces, piece *pieces)
{
     //verification of parameters
     if(pieces==NULL || nb_pieces<=0 || pieces[0]==NULL || width<=0 || height<=0)
	  return NULL;

     game new_g = malloc (sizeof (*new_g));

     if (new_g==NULL){
	  fprintf(stderr,"Problem in the allocation of newGame!!!");
     }

     new_g->board = malloc (sizeof(*(new_g->board))*height);

     // initialization of the board
     for (int w= 0; w<width; ++w )
	  for (int h= 0; h<height; ++h)
	       new_g->board[h][w] = -1;

     //course of the board to place the pieces
     int x = 0;
     int y = 0;
     int w = 0;
     int h = 0;

     new_g->piece = malloc (nb_pieces * sizeof(*pieces));
     if (new_g->piece==NULL)
     {
	  fprintf(stderr,"Problem in allocation of piece in structure ");
	
     }
     
     
     for (; (new_g->nb_piece<nb_pieces) && (pieces[new_g->nb_piece]!=NULL); ++(new_g->nb_piece))
     {

	  x = get_x((cpiece)pieces[new_g->nb_piece]);
	  y = get_y((cpiece)pieces[new_g->nb_piece]);
	  w = get_width((cpiece)pieces[new_g->nb_piece]);
	  h = get_height((cpiece)pieces[new_g->nb_piece]);

	  new_g->piece[new_g->nb_piece] = new_piece(x, y, w, h, can_move_x((cpiece)pieces[new_g->nb_piece]), can_move_y((cpiece)pieces[new_g->nb_piece]));

	  //verification piece totally on the board
	  if (w==0 || h==0 || x+w>=width || y+h>=height)
	  {
	       fprintf (stderr, "Piece out of the size of the board");
			
	  }

	  //in this case we know that the piece is on horizontal line
	  if(h==1)
	  {
	       for (;x<w; ++x)
		    new_g->board[y][x] = new_g->nb_piece;
	  }
	  // in this case we know that the piece is on vertical line
	  if (w==1)
	  {
	       for(;y<h;++y)
		    new_g->board[y][x] = new_g->nb_piece;
	  }
	  //in this case we know that the piece is at minimum a square 2*2
	  else
	  {
	       for (;y<h;++y)
		    for(int tmp_x = x;tmp_x<w;++tmp_x)
			 new_g->board[y][tmp_x] = new_g->nb_piece;
	  }
     }
     //clean game if newGame->piece not corresponding to the nb_pieces of *piece
     if (new_g->nb_piece != nb_pieces)
     {
	  delete_game(new_g); // free of all we allocated before
	  new_g = NULL;
     }
     return new_g;
}

/**
 * Default case to create a game rush hour 6*6
 */
game new_game_hr (int nb_piece, piece *piece)
{
     return new_game(6,6,nb_piece,piece);
}

void delete_game (game g)
{
     if (g!=NULL)
     {
	  for (int i= 0; i < g->nb_piece; ++i)
	       delete_piece(g->piece[i]);
	  free(g->piece);
	  for (int h= 0; h< g->height; ++h)
	       free (g->board[h]);
	  free(g->board);
	  free(g);
     }
}

void copy_game(cgame src, game dst)
{
     if (src!=NULL && dst!=NULL)
     {
	  dst->nb_move = src->nb_move;
	  dst->nb_piece = src->nb_piece;
	  dst->width = src->width;
	  dst->height = src->height;

	  for (int h= 0; h<src->height; ++h)
	  {
	       for (int w= 0; w< src->width; ++w)
	       {
		    dst->board[h][w] = src->board[h][w];
	       }
	  }
	  for (int i= 0; i<src->nb_piece; ++i)
	       copy_piece((cpiece)src->piece[i],dst->piece[i]);
     }
}

int game_nb_pieces(cgame g)
{
     return g->nb_piece;
}

cpiece game_piece(cgame g, int piece_num)
{
     if (g->nb_piece<=piece_num)
	  return NULL;
     return (cpiece)g->piece[piece_num];
}

bool game_over_hr(cgame g)
{
     return get_x(g->piece[0])==game_width(g)-2 && get_y(g->piece[0])==game_height(g)-get_y(g->piece[0])-1;
}



bool play_move(game g, int piece_num, dir d, int distance)
{

     //piece_num on the board or not? 
     if(piece_num>=g->nb_piece && piece_num<0)
	  return false;
  
     int x = get_x(game_piece((cgame)g, piece_num));
     int y = get_y(game_piece((cgame)g, piece_num));
     int p_height = get_height(game_piece((cgame)g, piece_num));
     int p_width = get_width(game_piece((cgame)g, piece_num));
     int g_height = game_height((cgame)g);
     int g_width = game_width((cgame)g);

     //Comparison of all the rectangle of the possible movement
     if(can_move_y((cpiece)g->piece[piece_num]) && (d==UP || d==DOWN))
     {
	  int new_h = p_height + distance;
	  if (new_h>=0 && new_h<g_height)
	  {
	       piece tmp_p = new_piece (x, y, p_width, new_h, false, false);
	       if (!intersect(tmp_p, game_piece((cgame)g, piece_num)))
	       {
		    move_piece(g->piece[piece_num],d,distance);
		    g->nb_move +=d;
		    return true;
	       }
	  }
     }
     if(can_move_x((cpiece)g->piece[piece_num]) && (d==LEFT || d==RIGHT))
     {
	  int new_w = p_width + distance;
	  if (new_w>=0 && new_w<g_width)
	  {
	       piece tmp_p = new_piece (x, y, new_w, p_height, false, false);
	       if (!intersect(tmp_p, game_piece((cgame)g, piece_num)))
	       {
		    move_piece(g->piece[piece_num], d, distance);
		    g->nb_move +=d;
		    return true;
	       }
	  }
     }
     return false;
}

int game_nb_moves(cgame g)
{
     return g->nb_move;
}

int game_width(cgame g)
{
     return g->width;
}

int game_height(cgame g)
{
     return g->height;
}
int game_square_piece (game g, int x, int y)
{
     return g->board[y][x];
}

