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
 *Put all the pieces where the should be on the board
 *
 **/
static void positionning(game g, cpiece *pieces)
{
     // initialization of the board
     for (int h= 0; h<g->height; ++h)
	  for (int w= 0; w<g->width; ++w )
	       g->board[h][w] = -1;

     //course of the board to place the pieces
     for (int i=0; i<g->nb_piece; ++i)
     {
        int x = get_x(pieces[i]);
	int y = get_y(pieces[i]);
	int w = get_width(pieces[i]);
	int h = get_height(pieces[i]);

	//in this case we know that the piece is on horizontal line
	if(h==1)
	  {
	    for (int tmp_x=x; tmp_x<(w+x); ++tmp_x)
	      g->board[y][tmp_x] = i;
	  }
	// in this case we know that the piece is on vertical line
	if (w==1)
	  {
	    for(int tmp_y=y; tmp_y<(h+y); ++tmp_y)
	      g->board[tmp_y][x] = i;
	  }
	//in this case we know that the piece is at minimum a square 2*2
	else
	  {
	    for (int tmp_y=y; tmp_y<(h+y); ++tmp_y)
	      for(int tmp_x=x;tmp_x<(w+w);++tmp_x)
		g->board[tmp_y][tmp_x] = i;
	  }
     }
}

/**
 *Test if the piece is completly on the board
 *
 **/
static bool is_in_grid(cgame g, cpiece p)
{
    if (get_x(p)>=0 && get_x(p)+get_width(p)-1<game_width(g))
      if (get_y(p)>=0 && get_y(p)+get_height(p)-1<game_height(g))
          return true;
    return false;
}

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
  if (new_g==NULL)
      fprintf(stderr,"Problem in the allocation of newGame!!!\n");

  new_g->board = malloc (sizeof(*(new_g->board))*height);
  if (new_g->board==NULL)
      fprintf(stderr, "Problem in the allocation of newGame's board (height)\n");
  for (int j= 0; j<height; ++j)
  {
      new_g->board[j] = (int *) malloc (sizeof(*(new_g->board[j]))*width);
    if (new_g->board[j]==NULL)
      fprintf(stderr, "Probleme in the allocation of newGame's board (width)\n");
  }

  new_g->width = width;
  new_g->height = height;
  new_g->nb_move = 0;
  new_g->nb_piece = 0;

  new_g->piece = malloc (nb_pieces * sizeof(*pieces));
  if (new_g->piece==NULL)
      fprintf(stderr,"Problem in allocation of piece in structure\n");
     
  for (int i=0; i<nb_pieces; ++i)
  {
      //verification piece totally on the board
      if (!is_in_grid(new_g, pieces[i]))
	fprintf(stderr, "Piece %d out of board\n", i);

      new_g->piece[i] = new_piece(get_x(pieces[i]), get_y(pieces[i]), get_width(pieces[i]), get_height(pieces[i]), can_move_x(pieces[i]), can_move_y(pieces[i]));
      new_g->nb_piece += 1;
  }

  positionning(new_g, (cpiece*)new_g->piece);

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
       dst->nb_move = game_nb_moves(src);
       dst->nb_piece = game_nb_pieces(src);
       dst->width = game_width(src);
       dst->height = game_height(src);

       for (int i= 0; i<game_nb_pieces(src); ++i)
       {
	   if(dst->piece[i] == NULL)
	     dst->piece[i] = new_piece(0,0,0,0,true,true);
	   copy_piece((cpiece)src->piece[i],dst->piece[i]);
       }

       positionning(dst, (cpiece*)dst->piece);
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
     return get_x(g->piece[0])==game_width(g)-2 && get_y(g->piece[0])==game_height(g)-3;
}

bool play_move(game g, int piece_num, dir d, int distance)
{

     //piece_num on the board or not? 
     if(piece_num>=g->nb_piece || piece_num<0)
	 return false;
  
     int x = get_x(game_piece((cgame)g, piece_num));
     int y = get_y(game_piece((cgame)g, piece_num));
     int p_height = get_height(game_piece((cgame)g, piece_num));
     int p_width = get_width(game_piece((cgame)g, piece_num));

     //Comparison of all the rectangle of the possible movement
     if(can_move_y((cpiece)g->piece[piece_num]) && (d==UP || d==DOWN))
     {
         int new_h = 0;
         if (d==DOWN)
	 {
	     new_h = y - distance;
	 }
         else
	 {
  	     new_h = y + distance;
	 }
         piece tmp_p = new_piece (x, new_h, p_width, p_height, false, true);
         if (is_in_grid((cgame)g, (cpiece)tmp_p))
	 {
	     for (int i=0; i<game_nb_pieces(g); ++i)
	     {
	         if (piece_num!=i && intersect(tmp_p, g->piece[i]))
		     return false;
	     }
	     move_piece(g->piece[piece_num],d,distance);
	     g->nb_move += distance;
	     positionning(g, (cpiece*)g->piece);
	     return true;
	 }
     }
     if(can_move_x((cpiece)g->piece[piece_num]) && (d==LEFT || d==RIGHT))
     {
         int new_w = 0;
         if (d==LEFT)
	 {
	     new_w = x - distance;
	 }
         else 
	 {
	     new_w = x + distance;
	 }
         piece tmp_p = new_piece (new_w, y, p_width, p_height, true, false);
         if (is_in_grid((cgame)g, (cpiece)tmp_p))
	 {
	     for (int i=0; i<game_nb_pieces(g); ++i)
	     {
	         if (piece_num!=i && intersect(tmp_p, g->piece[i]))
		     return false;
	     }
	     move_piece(g->piece[piece_num],d,distance);
	     g->nb_move += distance;
	     positionning(g, (cpiece*)g->piece);
	     return true;
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


