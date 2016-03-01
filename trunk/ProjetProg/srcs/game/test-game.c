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
void set_up_start(piece pieces[])
{
  pieces[0]=new_piece_rh(0,3,true,true);
  pieces[1]=new_piece_rh(2,2,false,false);
  pieces[2]=new_piece_rh(2,5,true,true);
  pieces[3]=new_piece_rh(4,3,false,false);
  pieces[4]=new_piece_rh(5,2,true,false);
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
  pieces[0]=new_piece_rh(4,3,true,true);
  pieces[1]=new_piece_rh(2,0,false,false);
  pieces[2]=new_piece_rh(2,5,true,true);
  pieces[3]=new_piece_rh(4,0,false,false);
  pieces[4]=new_piece_rh(5,4,true,false);
}

/**
 *@brief test if the function "game_piece" return the good piece.
 */
bool test_game_piece(cgame g)
{
  piece dst=malloc(sizeof(piece));
  if(dst==NULL)
  {
    fprintf(stderr,"Allocation memory error!\n");
    exit(EXIT_FAILURE);
  }
  cpiece cdst=dst;
  bool result=true;
  for(int i=0;i<NB_PIECES;i++)
    {
      cdst=game_piece(g,i);
      result = result && test_equality_int(get_height(g->pieces[i]), get_height(cdst), "copy get_height");
      result = result && test_equality_int(get_width(g->pieces[i]), get_width(cdst), "copy get_width");
      result = result && test_equality_int(get_x(g->pieces[i]), get_x(cdst), "copy get_x");
      result = result && test_equality_int(get_y(g->pieces[i]), get_y(cdst), "copy get_y");
      result = result && test_equality_bool(is_horizontal(g->pieces[i]), is_horizontal(cdst), "copy is_horizontal");
    }
  free(dst);
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
  game dst=malloc(sizeof(game));
  if(dst==NULL)
    {
      fprintf(stderr,"Allocation memory error!\n");
      exit(EXIT_FAILURE);
    }
  copy_game(src,dst);
  result=result && test_equality_int(NB_PIECES,game_nb_pieces(dst),"test_copy");
  result=result && test_equality_int(0,game_nb_moves(src),"game_nb_moves\n");
  for(int i=0;i<NB_PIECES;i++)
    {
      result = result && test_equality_int(get_height(src->pieces[i]), get_height(dst->pieces[i]), "copy get_height");
      result = result && test_equality_int(get_width(src->pieces[i]), get_width(dst->pieces[i]), "copy get_width");
      result = result && test_equality_int(get_x(src->pieces[i]), get_x(dst->pieces[i]), "copy get_x");
      result = result && test_equality_int(get_y(src->pieces[i]), get_y(dst->pieces[i]), "copy get_y");
      result = result && test_equality_bool(is_horizontal(src->pieces[i]), is_horizontal(dst->pieces[i]), "copy is_horizontal");
    }
  free(dst);
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
      result = result && test_equality_int(get_height(g->pieces[i]), get_height(verif[i]), "copy get_height");
      result = result && test_equality_int(get_width(g->pieces[i]), get_width(verif[i]), "copy get_width");
      result = result && test_equality_int(get_x(g->pieces[i]), get_x(verif[i]), "copy get_x");
      result = result && test_equality_int(get_y(g->pieces[i]), get_y(verif[i]), "copy get_y");
      result = result && test_equality_bool(is_horizontal(g->pieces[i]), is_horizontal(verif[i]), "copy is_horizontal");
      delete_piece(verif[i]);
    }
  return result;
}

int main(int argc,char * argv[])
{
  bool result=true;
  piece pieces[NB_PIECES];
  set_up_start(pieces);
  game g;
  g=new_game_hr(NB_PIECES,pieces);

  result=result && test_equality_bool(true,test_allocation(g,"g"),"test_allocation");
  
  cgame ptr_g=g;
  
  result=result && test_equality_bool(false,game_over_hr(ptr_g),"game_over_hr");
  result=result && test_equality_bool(true,test_game_piece(ptr_g),"test_game_piece");
  result=result && test_equality_bool(true,test_copy(ptr_g),"test_copy");
  result=result && test_equality_bool(true,solve(g),"solve");
  result=result && test_equality_bool(false,game_over_hr(ptr_g),"game_over_hr");
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
  
