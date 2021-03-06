#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "piece.h"
#include "game.h"

#define NB_PIECES 5

/**
 *@brief test if boolean value is equal to expected. If not, displays an error message indicating expected, value and name of the tested function.
 *@return true if expected==value.
 *@param testF is the name of the tested function.
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

/**
 *@brief test if allocation of data was correctly made. If not, displays an error message indicating empty pointer.
 *@param ptr is the tested pointer.
 *@return true if pointer!=NULL.
 */
bool test_allocation(void *ptr,char *name_ptr)
{
  if(ptr==NULL)
    {
      fprintf(stderr,"ERROR: pointer %s was not correctly allocated!",name_ptr);
    }
  return ptr!=NULL;
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
void set_up_start(piece pieces[],int length)
{
  pieces[0]=new_piece_rh(0,3,true,true);
  pieces[1]=new_piece_rh(2,0,false,false);
  pieces[2]=new_piece_rh(2,5,true,true);
  pieces[3]=new_piece_rh(4,3,false,false);
  pieces[4]=new_piece_rh(5,3,true,false);
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
  pieces[0]=new_piece_rh(3,3,true,true);
  pieces[1]=new_piece_rh(2,0,false,false);
  pieces[2]=new_piece_rh(2,5,true,true);
  pieces[3]=new_piece_rh(4,0,false,false);
  pieces[4]=new_piece_rh(5,1,true,false);
}

/**
 *@brief test if a game is correctly created.
 */
bool test_new_game()
{
  bool result=true;
  piece tab[NB_PIECES];
  set_up_start(tab,NB_PIECES);
  game g=new_game_hr(NB_PIECES,tab);
  result=result && test_equality_int(NB_PIECES,game_nb_pieces(g),"new_game_hr nbPiece");
  result=result && test_equality_int(0,game_nb_moves(g),"new_game_hr nbMove");
  for(int i=0;i<NB_PIECES;i++)
    {
      result = result && test_equality_int(get_height(tab[i]), get_height(game_piece(g,i)), "new_game get_height");
      result = result && test_equality_int(get_width(tab[i]), get_width(game_piece(g,i)), "new_game get_width");
      result = result && test_equality_int(get_x(tab[i]), get_x(game_piece(g,i)), "new_game get_x");
      result = result && test_equality_int(get_y(tab[i]), get_y(game_piece(g,i)), "new_game get_y");
      result = result && test_equality_bool(is_horizontal(tab[i]), is_horizontal(game_piece(g,i)), "new_game is_horizontal");
    }
  return result;
}


/**
 *@brief test if a copy of a game was correctly made.
 *@param src is constant pointer on a game.
 *@return true is the copy is correct.
 */
bool test_copy(cgame src)
{
  bool result=true;
  piece tab[NB_PIECES];
  game dst=new_game_hr(NB_PIECES,tab);
  copy_game(src,dst);
  result=result && test_equality_int(NB_PIECES,game_nb_pieces(dst),"test_copy");
  result=result && test_equality_int(0,game_nb_moves(src),"game_nb_moves\n");
  for(int i=0;i<NB_PIECES;i++)
    {
      result = result && test_equality_int(get_height(game_piece(src,i)), get_height(game_piece(dst,i)), "copy get_height");
      result = result && test_equality_int(get_width(game_piece(src,i)), get_width(game_piece(dst,i)), "copy get_width");
      result = result && test_equality_int(get_x(game_piece(src,i)), get_x(game_piece(dst,i)), "copy get_x");
      result = result && test_equality_int(get_y(game_piece(src,i)), get_y(game_piece(dst,i)), "copy get_y");
      result = result && test_equality_bool(is_horizontal(game_piece(src,i)), is_horizontal(game_piece(dst,i)), "copy is_horizontal");
    }
  return result;
}

/**
 *@brief solve the test configuration game.
 *@return true if the game was solved without errors.
 */
bool solve(game g,cgame cg)
{
  bool result=true;
  int nb_mov=0;
  result=result && test_equality_bool(false,play_move(g,1,UP,3),"play_move");
  result=result && test_equality_bool(false,play_move(g,2,RIGHT,1),"play_move");
  result=result && test_equality_bool(true,play_move(g,3,DOWN,3),"play_move");
  nb_mov+=3;
  result=result && test_equality_bool(true,play_move(g,4,DOWN,2),"play_move");
  nb_mov+=2;
  result=result && test_equality_bool(false,play_move(g,4,DOWN,2),"play_move");
  result=result && test_equality_bool(false,play_move(g,1,LEFT,1),"play_move");
  result=result && test_equality_bool(true,play_move(g,0,RIGHT,4),"play_move");
  nb_mov+=4;
  result=result && test_equality_int(nb_mov,game_nb_moves(cg),"nb_move_game");
  piece verif[NB_PIECES];
  set_up_winning(verif);
  for(int i=0;i<NB_PIECES;i++)
    {
      result = result && test_equality_int(get_height(game_piece(g,i)), get_height(verif[i]), "copy get_height");
      result = result && test_equality_int(get_width(game_piece(g,i)), get_width(verif[i]), "copy get_width");
      result = result && test_equality_int(get_x(game_piece(g,i)), get_x(verif[i]), "copy get_x");
      result = result && test_equality_int(get_y(game_piece(g,i)), get_y(verif[i]), "copy get_y");
      result = result && test_equality_bool(is_horizontal(game_piece(g,i)), is_horizontal(verif[i]), "copy is_horizontal");
      delete_piece(verif[i]);
    }
  return result;
}

int main(int argc,char * argv[])
{
  bool result=true;
  piece pieces[NB_PIECES];
  set_up_start(pieces,NB_PIECES);

  result=result && test_equality_bool(true,test_new_game(),"test_new_game");

  game g=new_game_hr(NB_PIECES,pieces);
  cgame cg=(cgame)g;
  
  result=result && test_equality_bool(false,game_over_hr(cg),"game_over_hr start");
  result=result && test_equality_bool(true,test_copy(cg),"test_copy");
  result=result && test_equality_bool(true,solve(g,cg),"solve");
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
  
