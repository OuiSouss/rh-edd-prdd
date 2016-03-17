#include "game.h"
#include <stdlib.h>
#include <stdio.h>

struct game_s {
  int** board;
  int width;
  int height;
  int nbMove;
  piece* piece;
  int nbPiece;
};


/**
* In this Version, we are doing the hypothesis that the redPiece the
* piece 0 is in *piece.
* So, we are in need doing the test if the first piece is present.
* We also supposed that *piece != NULL
*
*
 **/
game new_game (int width, int height, int nb_pieces, piece *pieces){
  game newGame = (game) malloc (sizeof (*newGame));

  if (newGame == NULL){
    fprintf(stderr,"Problem in the alloc of newGame!!!");
    exit(EXIT_FAILURE);
  }

  newGame->board = (int **) malloc (sizeof(*(newGame->board))*height);

  if (newGame->board == NULL){
    fprintf(stderr, "Problem in the alloc of newGame's board");
    exit(EXIT_FAILURE);
  }

  for (int j= 0; j<height; ++j)
    newGame->board[j] = (int *) malloc (sizeof(*(newGame->board[j]))*width);

  //look if piece in parameter don't intersect
  for (int i= 0; i<nb_pieces -2; ++i){
    for (int j= i+1; j<nb_pieces - 1; ++j){
      if (intersect (pieces[i], pieces[j])){
    	  fprintf(stderr," Conflict of intersect between pieces! Change parameter\n");
    	  exit(EXIT_FAILURE);
      }
    }
  }

  newGame->width = width;
  newGame->height = height;
  newGame->nbMove = 0;
  newGame->nbPiece = nb_pieces + 1;

  // initialization of the board
  for (int w = 0; w<width; ++w )
	  for (int h = 0; h<height; ++h)
		  newGame->board[h][w] = -1;

  //course of the board to place the pieces
  int x = 0;
  int y = 0;
  int w= 0;
  int h = 0;

  if( pieces != NULL){
      for (int p=0; p<nb_pieces; ++p){
        x = get_x((cpiece)pieces[p]);
        y = get_y((cpiece)pieces[p]);
        w = get_width((cpiece)pieces[p]);
        h = get_height((cpiece)pieces[p]);
        if ( w==0 || h==0 || x+w >= width || y+h>= height){
        	fprintf (stderr, "Piece out of the size of the board");
        	exit(EXIT_FAILURE);
        }
        if(h == 1){ //in this case we know that the piece is on horizontal line
        	for (;x<w; ++x)
        		newGame->board[y][x] = p;
        }
        if (w == 1){ // in this case we know that the piece is on vertical line
        		for(;y<h;++y)
        			newGame->board[y][x] = p;
        }
        else{ //in this case we know that the piece is at minimum a square 2*2
        	for (;y<h;++y)
        		for(int tmp_x = x;tmp_x<w;++tmp_x)
        			newGame->board[y][tmp_x] = p;
        }
      }
  }
  newGame->piece = pieces;
  return newGame;

}

game new_game_hr (int nb_piece, piece *piece){
	//question demander taille

	return new_game(6,6,nb_piece,piece);
}

void delete_game (game g){
  for (int i = 0; i < g->nbPiece; ++i)
    delete_piece(g->piece[i]);
  free(g->piece);
  for (int h = 0; h< g->height; ++h)
	  for (int w = 0; w< g->width; ++w)
		  free (&(g->board[h][w]));
  free(g->board);

  free(g);
}

void copy_game(cgame src, game dst){
  if (src!=NULL && dst!=NULL){
    dst->nbMove = src->nbMove;
    dst->nbPiece = src->nbPiece;
    dst->width = src->width;
    dst->height = src->height;

    for (int h =0; h< src->height; ++h){
      for (int w =0; w< src->width; ++w){
    	  dst->board[h][w] = src->board[h][w];
      }
    }
    for (int i=0; i<src->nbPiece; ++i)
      dst->piece[i] = src->piece[i];

    
  }
}

int game_nb_pieces(cgame g){
  return g->nbPiece;
}

cpiece game_piece(cgame g, int piece_num){
  if (g->nbPiece <= piece_num)
    return NULL;
  return (cpiece)g->piece[piece_num];
}

bool game_over_hr(cgame g){
  if( get_x(g->piece[0])==4 && get_y(g->piece[0])==3)
    return true;
  return false;
}

bool play_move(game g, int piece_num, dir d, int distance){
  /*
  //piece_num on the board or not? 
  if(piece_num >= g->nbPiece)
    return false;
  
  //Test with the redCar first
  else if(piece_num == 0){
    //Direction correspond with the type of piece
    if (d == UP || d == DOWN)
      return false;
    //copy the redCar to do the move on the copy
    piece copyPiece = new_piece_rh(0,0,true,true);
    copy_piece((cpiece)g->redCar, copyPiece);

    //move of the copy 
    move_piece(copyPiece,d,distance);

    // on the board or not
    if((get_x(copyPiece)<0 || get_x(copyPiece)>5) && (get_y(copyPiece)<0 || get_y(copyPiece)>5)){
      delete_piece(copyPiece);
      return false;
    }

    //copy not intersect with other pieces?
    for(int i=0; i<g->nbPiece -2; ++i){
      if(intersect((cpiece)copyPiece,(cpiece)(g->piece[i])))
	{
	  delete_piece(copyPiece);
	  return false;
	}
    }
    copy_piece((cpiece)copyPiece, g->redCar);
    g->nbMove += d ;
    delete_piece(copyPiece);
    return true;
  }
  
  //case of piece_num part of piece[]
  else{
    
    //Test direction compatible
    if(is_horizontal(g->piece[piece_num -1]) && (d==UP || d==DOWN))
      return false;
    else if(!is_horizontal(g->piece[piece_num -1]) && (d==LEFT || d==RIGHT))
      return false;

    //copy piece
    piece copyPiece = new_piece_rh(0,0,true,true);
    copy_piece(g->piece[piece_num],copyPiece);

    //move on the copy
    move_piece(copyPiece,d,distance);

    //Test on the board
    if((get_x(copyPiece)<0 || get_x(copyPiece)>5) && (get_y(copyPiece)<0 || get_y(copyPiece)>5)){
      delete_piece(copyPiece);
      return false;
    }

    //test intersect with other piece
    if(intersect((cpiece)copyPiece, (cpiece)g->redCar))
      return false;

    //parcours de la partie gauche du tableau de piece du jeu autour de la piece a comparer
    int i= 0;
    for(;i!= piece_num - 1 ;++i)
      if(intersect(copyPiece,g->piece[i]))
	 return false;
    i+=2;
    //parcours de la partie droite du tableau de piece du jeu autour de la piece a comparer
    for(;i!=g->nbPiece-2;++i)
      if(intersect(copyPiece,g->piece[i]))
	return false;

    copy_piece((cpiece)copyPiece,g->piece[piece_num]);
    g->nbMove += d;
    return true;
    }*/
  return false;

}

int game_nb_moves(cgame g){
  return g->nbMove;
}

int game_width(cgame g){
  return g->width;
}

int game_height(cgame g){
  return g->height;
}
int game_square_piece (game g, int x, int y){
  return g->board[y][x];
}
game g, int x, int y){
  if ( g->board[y][x] == -1)
    return -1;
  return g->board[y][x];
}
