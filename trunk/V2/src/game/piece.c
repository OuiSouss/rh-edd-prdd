#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "piece.h"

/**
 *@file piece.c
 *
 *@brief Fonctions relating to pieces.
 *
 **/

struct piece_s
{
  int x;
  int y;
  int width;
  int height;
  bool move_x;
  bool move_y;
};


// Version only available for Rush Hour
piece new_piece_rh(int x, int y, bool small, bool horizontal)
{
  piece p = malloc(sizeof(*p));
  if (p==NULL)
  {
    fprintf(stderr, "Allocation probleme");
    exit(EXIT_FAILURE);
  }
  p->x = x;
  p->y = y;
  // Set width/height at the maximum value before diminushing it if the piece is set as "samll"
  if (horizontal)
  {
    p->width = 3;
    p->height = 1;
    p->move_x = true;
    p->move_y = false;
    if (small)
      p->width -= 1;
  }
  else
  {
    p->width = 1;
    p->height = 3;
    p->move_x = false;
    p->move_y = true;
    if (small)
      p->height -= 1;
  }
  return p;
}

void delete_piece(piece p)
{
  if (p!=NULL)
  {
    free(p);
  }
}

void copy_piece(cpiece src, piece dst)
{
  if (src!=NULL && dst!=NULL)
  {
    dst->x = src->x;
    dst->y = src->y;
    dst->width = src->width;
    dst->height = src->height;
    dst->move_x = src->move_x;
    dst->move_y = src->move_y;
  }
  else
  {
    fprintf(stderr, "At least one piece is invalid");
  }
}

void move_piece(piece p, dir d, int distance)
{
  if (can_move_x(p))
  {
    if (d==LEFT)
      p->x -= distance;
    else if (d == RIGHT)
      p->x += distance;
  }
  if (can_move_y(p))
  {
    if (d == UP)
      p->y += distance;
    else if (d == DOWN)
      p->y -= distance;
  }
}

/*
Former version of the fonction intersect 

bool intersect(cpiece p1, cpiece p2)
{
  if (get_x(p1) == get_x(p2) && get_y(p1) == get_y(p2))
    return true;
  if (is_horizontal(p1))
  {
    if (is_horizontal(p2))
    {
      if (get_y(p1) != get_y(p2))
	return false;
      if ( (((get_x(p1)+get_width(p1)) > get_x(p2)) && (get_x(p1) < (get_x(p2)+get_width(p2))))  ||  (((get_x(p2)+get_width(p2)) > get_x(p1)) && (get_x(p2) < (get_x(p1)+get_width(p1)))) )
	return true;
      return false;
    }
    if ( (get_y(p1) < get_y(p2))  ||  (get_y(p1) > (get_y(p2)+get_height(p2)-1)) )
      return false;
    if ( (get_x(p1) <= get_x(p2)) && (get_x(p1)+get_width(p1) > get_x(p2)) )
      return true;
    return false;
  }
  if (!is_horizontal(p2))
  {
    if (get_x(p1) != get_x(p2))
      return false;
    if ( (((get_y(p1)+get_height(p1)) > get_y(p2)) && (get_y(p1) < (get_y(p2)+get_height(p2))))  ||  (((get_y(p2)+get_height(p2)) > get_y(p1)) && (get_y(p2) < (get_y(p1)+get_height(p1)))) )
	return true;
    return false;
  }
  if ( (get_y(p2) < get_y(p1))  ||  (get_y(p2) > (get_y(p1)+get_height(p1)-1)) )
    return false;
  if ( (get_x(p2) <= get_x(p1)) && (get_x(p2)+get_width(p2) > get_x(p1)) )
    return true;
  return false;
}
*/

bool intersect (cpiece p1, cpiece p2)
{
  // Test if pieces have the same bottom-left coordonate
  if (get_x(p1) == get_x(p2) && get_y(p1) == get_y(p2)) 
    return true;
  int x1=get_x(p1);
  int x2=get_x(p2);
  int y1=get_y(p1);
  int y2=get_y(p2);
  // Test if the left coordonate of p1 is at the left of the right of p2 and if the right coordonate of p1 is at the right of left coordonate of p2
  // Also test if the bottom coordonate of p1 is at the bottom of the top coordonate of p2 and if the top coordonate of p1 is at the top of the bottom coordonate of p2
  if ((x1 < x2+get_width(p2)) && (x1+get_width(p1) > x2))
    if ((y1 < y2+get_height(p2)) && (y1+get_height(p1) > y2))
      return true;
  return false;
}
  
int get_x(cpiece p)
{
  return p->x;
}

int get_y(cpiece p)
{
  return p->y;
}

int get_height(cpiece p)
{
  return p->height;
}

int get_width(cpiece p)
{
  return p->width;
}

bool is_horizontal(cpiece p)
{
  return can_move_x(p) && !can_move_y(p);
}

bool can_move_x(cpiece p)
{
  return p->move_x;
}

bool can_move_y(cpiece p)
{
  return p->move_y;
}

// Version of new_piece available for the game Ane Rouge
piece new_piece(int x, int y, int width, int height, bool move_x, bool move_y)
{
  piece p = malloc(sizeof(*p));
  if (p==NULL)
  {
    fprintf(stderr, "Allocation probleme");
    exit(EXIT_FAILURE);
  }
  p->x = x;
  p->y = y;
  p->width = width;
  p->height = height;
  p->move_x = move_x;
  p->move_y = move_y;
  return p;
}


