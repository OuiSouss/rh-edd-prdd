#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "piece.h"
#include "game.h"

#define NB_PIECES 5
#define WIDTH_GAME 6
#define HEIGHT_GAME 6

/**
 *@brief test if boolean value is equal to expected. If not, displays an error message indicating expected, value and name of the tested function.
 *@param testF is the name of the tested function.
 *@return true if expected==value.
 */
bool test_equality_bool(bool expected, bool value, char *testF)
{
  if(expected!=value)
    {
      fprintf(stderr,"ERROR: expected %d is different to value %d in tested function: %s!\n",expected,value,testF);
    }
  return expected==value;
}

/**
 *@brief test if integer value is equal to expected. If not, displays an error message indicating expected, value and name of the tested function.
*@param testF is the name of the tested function.
 *@return true if expected==value.
 */
bool test_equality_int(int expected, int value, char *testF)
{
  if(expected!=value)
    {
      fprintf(stderr,"ERROR: expected %d is different to value %d in tested function: %s!\n",expected,value,testF);
    }
  return expected==value;
}

/*test configuration
..223.
....34
00..34
..1...
..1...
..1...
*/

/**
 *@brief change a "piece" table by  writting the cars' coodonates of the test configuration(see above) into it.
 *@param piece array of pieces.
 */
void set_up_start(piece pieces[])
{
  pieces[0]=new_piece(0,3,2,1,true,false);
  pieces[1]=new_piece(2,0,1,3,false,true);
  pieces[2]=new_piece(2,5,2,1,true,false);
  pieces[3]=new_piece(4,3,1,3,false,true);
  pieces[4]=new_piece(5,3,1,2,false,true);
}

void delete_set_up(piece pieces[],int length)
{
  for(int i=0;i<length;i++)
    {
      delete_piece(pieces[i]);
    }
}
  

/*winning configuration
..22..
......
....00
..1.34
..1.34
..1.3.
*/


/**
 *@brief change a "piece" table by  writting the cars' coodonates of the winning configuration(see above) into it.
 *@param piece array of pieces.
 */
void set_up_winning(piece pieces[])
{
  pieces[0]=new_piece(4,3,2,1,true,false);
  pieces[1]=new_piece(2,0,1,3,false,true);
  pieces[2]=new_piece(2,5,2,1,true,false);
  pieces[3]=new_piece(4,0,1,3,false,true);
  pieces[4]=new_piece(5,1,1,2,false,true);
}

/**
 *@brief test if a game is correctly created.
 */
bool test_new_game()
{
  printf("Test of the function \"new_game\".\n");
  bool result=true;
  piece tab[NB_PIECES];
  set_up_start(tab);
  game g=new_game(WIDTH_GAME,HEIGHT_GAME,NB_PIECES,tab);
  printf("Good width?\n");
  result=result && test_equality_int(WIDTH_GAME,game_width(g),"new_game game_width");
  printf("Good height?\n");
  result=result && test_equality_int(HEIGHT_GAME,game_height(g),"new_game game_height");
  printf("Good number of pieces?\n");
  result=result && test_equality_int(NB_PIECES,game_nb_pieces(g),"new_game nbPiece");
  printf("Good number of moves?\n");
  result=result && test_equality_int(0,game_nb_moves(g),"new_game nbMove");
  printf("Good pieces?\n");
  for(int i=0;i<NB_PIECES;i++)
    {
      printf("\tChecking piece number %d.",i);
      result = result && test_equality_int(get_height(tab[i]), get_height(game_piece(g,i)), "new_game get_height");
      result = result && test_equality_int(get_width(tab[i]), get_width(game_piece(g,i)), "new_game get_width");
      result = result && test_equality_int(get_x(tab[i]), get_x(game_piece(g,i)), "new_game get_x");
      result = result && test_equality_int(get_y(tab[i]), get_y(game_piece(g,i)), "new_game get_y");
      result = result && test_equality_bool(can_move_x(tab[i]), can_move_x(game_piece(g,i)), "new_game can_move_x");
      result = result && test_equality_bool(can_move_y(tab[i]), can_move_y(game_piece(g,i)), "new_game can_move_y");
    }
  return result;
  printf("Done.\n\n");
}

/**
 *@brief test if a copy of a game was correctly made.
 *@param src is constant pointer on a game.
 *@return true is the copy is correct.
 */

bool test_copy(cgame src)
{
  printf("Test of the function \"copy_game\".\n");
  bool result=true;
  piece tab[NB_PIECES];
  set_up_start(tab);
  game dst=new_game(10,10,NB_PIECES,tab);
  printf("Copy of the source game to the destination game\n");
  copy_game(src,dst);
  printf("Same number of pieces?\n");
  result=result && test_equality_int(NB_PIECES,game_nb_pieces((cgame)dst),"test_copy");
  printf("Same number of moves?\n");
  result=result && test_equality_int(0,game_nb_moves(src),"game_nb_moves\n");
  printf("Same pieces?\n");
  for(int i=0;i<NB_PIECES;i++)
    {
      printf("\tChecking piece number %d.\n",i);
      result = result && test_equality_int(get_height(game_piece(src,i)), get_height(game_piece(dst,i)), "copy get_height");
      result = result && test_equality_int(get_width(game_piece(src,i)), get_width(game_piece(dst,i)), "copy get_width");
      result = result && test_equality_int(get_x(game_piece(src,i)), get_x(game_piece(dst,i)), "copy get_x");
      result = result && test_equality_int(get_y(game_piece(src,i)), get_y(game_piece(dst,i)), "copy get_y");
      result = result && test_equality_bool(can_move_x(game_piece(src,i)), can_move_x(game_piece(dst,i)), "copy can_move_x");
      result = result && test_equality_bool(can_move_y(game_piece(src,i)), can_move_y(game_piece(dst,i)), "copy can_move_y");
    }
  printf("Done.\n\n");
  return result;
}

/**
 *@brief solve the test configuration game.
 *@return true if the game was solved without errors.
 */
bool solve(game g,cgame cg)
{
  printf("Try to solve the game.\n");
  bool result=true;
  int nb_mov=0;
  printf("Move the piece 1 up 3 times (bad move).\n");
  result=result && test_equality_bool(false,play_move(g,1,UP,3),"play_move");
  printf("Move the piece 2 right once (bad move).\n");
  result=result && test_equality_bool(false,play_move(g,2,RIGHT,1),"play_move");
  printf("Move the piece 3 down three times (good move).\n");
  result=result && test_equality_bool(true,play_move(g,3,DOWN,3),"play_move");
  nb_mov+=3;
  printf("Move the piece 4 down twice (good move).\n");
  result=result && test_equality_bool(true,play_move(g,4,DOWN,2),"play_move");
  nb_mov+=2;
  printf("Move the piece 4 down twice (bad move).\n");
  result=result && test_equality_bool(false,play_move(g,4,DOWN,2),"play_move");
  printf("Move the piece 1 left once (bad move).\n");
  result=result && test_equality_bool(false,play_move(g,1,LEFT,1),"play_move");
  printf("Move the piece 0 right four times (good move).\n");
  result=result && test_equality_bool(true,play_move(g,0,RIGHT,4),"play_move");
  nb_mov+=4;
  printf("Good number of moves?\n");
  result=result && test_equality_int(nb_mov,game_nb_moves(cg),"nb_move_game");
  piece verif[NB_PIECES];
  set_up_winning(verif);
  printf("Check if the pieces did the good moves.\n");
  for(int i=0;i<NB_PIECES;i++)
    {
      printf("\tChecking the piece number %d\n",i);
      result = result && test_equality_int(get_height(game_piece(g,i)), get_height(verif[i]), "solve get_height");
      result = result && test_equality_int(get_width(game_piece(g,i)), get_width(verif[i]), "solve get_width");
      result = result && test_equality_int(get_x(game_piece(g,i)), get_x(verif[i]), "solve get_x");
      result = result && test_equality_int(get_y(game_piece(g,i)), get_y(verif[i]), "solve get_y");
      result = result && test_equality_bool(can_move_x(game_piece(g,i)), can_move_x(verif[i]), "solve can_move_x");
      result = result && test_equality_bool(can_move_y(game_piece(g,i)), can_move_y(verif[i]), "solve can_move_y");
      delete_piece(verif[i]);
    }
  printf("Done.\n\n");
  return result;
}

/**
 *@brief test if the function "game_square_piece" return the good piece of the board.
 *@param game
 *@return true if there is no error with the returned results.
 */
bool test_game_square_piece(game g)
{
  printf("Test of the function \"game_square_piece\".\n");
  bool result=true;
  printf("Piece on the square :\n\t(0;0);\n");
  result=result && test_equality_int(-1,game_square_piece(g,0,0),"test_game_square_piece -1");
  printf("\t(0;3);\n");
  result=result && test_equality_int(0,game_square_piece(g,0,3),"test_game_square_piece 0");
  printf("\t(2;0);\n");
  result=result && test_equality_int(1,game_square_piece(g,2,0),"test_game_square_piece 1");
  printf("\t(3;5);\n");
  result=result && test_equality_int(2,game_square_piece(g,3,5),"test_game_square_piece 2");
  printf("\t(4;5);\n");
  result=result && test_equality_int(3,game_square_piece(g,4,5),"test_game_square_piece 3");
  printf("\t(5;4).\n");
  result=result && test_equality_int(4,game_square_piece(g,5,4),"test_game_square_piece 4");
  printf("Done.\n\n");
  return result;
}

int main()
{
  bool result=true;
  piece pieces[NB_PIECES];
  printf("Initialisation of the table \"pieces\" with the pieces :\n");
  set_up_start(pieces);
  for(int i = 0; i < NB_PIECES ; i++)
    printf("Piece number %d : coordonates ( %d ; %d) , width = %d , height = %d , can move x? %s , can move y? %s\n",i,get_x(pieces[i]) , get_y(pieces[i]) , get_width(pieces[i]) , get_height(pieces[i]) , can_move_x(pieces[i])? "yes":"no",can_move_y(pieces[i])? "yes":"no");
  printf("\n");

  result=result && test_equality_bool(true,test_new_game(),"test_new_game");

  game g=new_game(WIDTH_GAME,HEIGHT_GAME,NB_PIECES,pieces);
printf("Initialisation of the game \"g\" :\nwidth = %d , height = %d , number of pieces = %d , table used : pieces\n",game_width(g),game_height(g),game_nb_pieces(g));
  cgame cg=(cgame)g;
  
  result=result && test_equality_bool(true,test_game_square_piece(g),"game_square_piece");
  result=result && test_equality_bool(false,game_over_hr(cg),"game_over_hr start");
  result=result && test_equality_bool(true,solve(g,cg),"solve");
  //result=result && test_equality_bool(true,test_copy(cg),"test_copy");
  result=result && test_equality_bool(true,game_over_hr(cg),"game_over_hr end");
  delete_set_up(pieces,NB_PIECES);
  if(result==true)
    {
      printf("\"Game\" module is correct!\n");
      return EXIT_SUCCESS;
    }
  else
    {
      printf("\"Game\" module have yet some errors!\n");
      return EXIT_FAILURE;
    }
}
  
