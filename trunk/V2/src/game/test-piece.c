#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "piece.h"

#define NB_PIECES 4

/**
 * @brief test if value is equal to expected; if not, displays an error message containing msg to standard error output 
 * @return true if expected==value
 */
bool test_equality_int(int expected, int value, char * msg) 
{
  if (expected != value)
    fprintf(stderr,"ERR: value expected %d ; value computed %d. %s\n", expected, value, msg);
  return expected == value;
}

/**
 * @brief test if value is equal to expected; if not, displays an error message containing msg to standard error output 
 */
bool test_equality_bool(bool expected, bool value, char * msg) 
{
  if (expected != value)
    fprintf(stderr,"ERR: value expected %d ; value computed %d. %s\n", expected, value, msg);
  return expected == value;
}

piece pieces[NB_PIECES];
/* configue de test
.....3
.....3
...003
......
...122
...1..
 */
void set_up() 
{
  pieces[0] = new_piece(3, 3, 2, 1, true, false);
  pieces[1] = new_piece(3, 0, 1, 2, false, true);
  pieces[2] = new_piece(4, 1, 2, 1, true, false);
  pieces[3] = new_piece(5, 3, 1, 3, true, false);
}
void tear_down() 
{
  for (int i = 0 ; i < NB_PIECES; i++)
    delete_piece(pieces[i]);
}

bool test_new_piece() 
{
  printf("Test of the function \"new_piece\".\n");
  bool result = true;
  for (int x= 0 ; x < 5; x++)
    for (int y= 0 ; y < 5; y++)
      for (int w= 1 ; w < 5 ; w++)
	for (int h= 1 ; h < 5 ; h++)
	  for (bool move_x= false; !move_x ; move_x= !move_x)
	    for (bool move_y= false; !move_y ; move_y= !move_y)
	      {
		piece p = new_piece(x, y, w, h, move_x, move_y);
		result = result && test_equality_int(x, get_x(p),"get_x");
		result = result && test_equality_int(y, get_y(p),"get_y");
		result = result && test_equality_int(w, get_width(p),"get_width");
		result = result && test_equality_int(h, get_height(p),"get_height");
		result = result && test_equality_bool(move_x,can_move_x(p),"can_move_x");
		result = result && test_equality_bool(move_y,can_move_y(p),"can_move_y");
		delete_piece(p);
	      }
  printf("Done.\n");
  return result;
}

bool test_intersect() 
{
  printf("Test of the function \"intersect\".\n");
  bool result = true;
  set_up();
  printf("Does each piece intesects with itself ?\n");
  for (int i=0; i < NB_PIECES; i++)
    for (int j =0; j<NB_PIECES; j++)
      result = result && test_equality_bool(i==j, intersect(pieces[i], pieces[j]),"intersect");

  piece pb_piece1 = new_piece(3, 3, 1, 3, false, true);
  piece pb_piece2 = new_piece(3, 1, 1, 3, false, true);
  printf("Test of particular intersection case.\n");
  result = result && test_equality_bool(true, intersect(pieces[0], pb_piece1),"intersect pb1");
  result = result && test_equality_bool(true, intersect(pb_piece2, pb_piece1),"intersect pb2");
  tear_down();
  printf("Done.\n");
  return result;
}

bool test_move() 
{
  printf("Test of the function \"move_piece\".\n");
  bool result = true;
  piece p = new_piece(0, 0, 2, 1, true, false);
  set_up();
  for (int dist = 1; dist < NB_PIECES; dist++)
    for (int i=0; i < NB_PIECES; i++) 
      {
	printf("Try to move the piece %d\n");
	copy_piece(pieces[i],p);
	printf("\t-left;\n");
	move_piece(p, LEFT, dist);
	if (can_move_x(pieces[i]))
	  result = result && test_equality_int(get_x(pieces[i])-dist,get_x(p),"move LEFT");
	else
	  result = result && test_equality_int(get_x(pieces[i]),get_x(p),"move LEFT");
	copy_piece(pieces[i],p);
	printf("\t-right;\n");
	move_piece(p, RIGHT, dist);
	if (can_move_x(pieces[i]))
	  result = result && test_equality_int(get_x(pieces[i])+dist,get_x(p),"move RIGHT");
	else
	  result = result && test_equality_int(get_x(pieces[i]),get_x(p),"move RIGHT");
	copy_piece(pieces[i],p);
	printf("\t-up;\n");
	move_piece(p, UP, dist);
	if (can_move_y(pieces[i]))
	  result = result && test_equality_int(get_y(pieces[i])+dist,get_y(p),"move UP");
	else
	  result = result && test_equality_int(get_y(pieces[i]),get_y(p),"move UP");
	copy_piece(pieces[i],p);
	printf("\t-down.\n");
	move_piece(p, DOWN, dist);
	if (can_move_y(pieces[i]))
	  result = result && test_equality_int(get_y(pieces[i])-dist,get_y(p),"move DOWN");
	else
	  result = result && test_equality_int(get_y(pieces[i]),get_y(p),"move DOWN");
      }
  tear_down();
  delete_piece(p);
  printf("Done.\n");
  return result;
}


bool test_copy() 
{
  printf("Test of the function \"copy_piece\".\n");
  piece p = new_piece(0, 0, 2, 1, true, false);
  bool result = true;
  set_up();
  for (int i = 0 ; i < NB_PIECES; i++) 
  {
    printf("Copy of the piece number %d.\n",i);
    copy_piece(pieces[i],p);
    result = result && test_equality_int(get_height(pieces[i]), get_height(p), "copy get_height");
    result = result && test_equality_int(get_width(pieces[i]), get_width(p), "copy get_width");
    result = result && test_equality_int(get_x(pieces[i]), get_x(p), "copy get_x");
    result = result && test_equality_int(get_y(pieces[i]), get_y(p), "copy get_y");
    result = result && test_equality_bool(can_move_x(pieces[i]), can_move_x(p), "copy can_move_x");
    result = result && test_equality_bool(can_move_y(pieces[i]), can_move_y(p), "copy can_move_y");
  }
  tear_down();
  delete_piece(p);
  printf("Done.\n");
  return result;
}

int main ()
{
  bool result= true;

  result = result && test_equality_bool(true, test_new_piece(), "new_piece");
  result = result && test_equality_bool(true, test_intersect(), "intersect");
  result = result && test_equality_bool(true, test_move(), "move");
  result = result && test_equality_bool(true, test_copy(), "copy");

  if (result) 
  {
    printf("Youpi !\n");
    return EXIT_SUCCESS;
  }
  else
    return EXIT_FAILURE;
}
