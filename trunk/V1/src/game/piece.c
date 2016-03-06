#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "piece.h"


struct piece_s
{
  int x;
  int y;
  bool small;
  bool horizontal;
};


piece new_piece_rh(int x, int y, bool small, bool horizontal)
{
  piece p = (piece) malloc(sizeof(*p));
  if (p==NULL)
  {
    fprintf(stderr, "Allocation probleme");
    exit(EXIT_FAILURE);
  }
  p->x = x;
  p->y = y;
  p->small = small;
  p->horizontal = horizontal;
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
    dst->small = src->small;
    dst->horizontal = src->horizontal;
  }
  else
  {
    fprintf(stderr, "At least one piece is invalid");
  }
}

void move_piece(piece p, dir d, int distance)
{
  if (is_horizontal(p))
  {
    if (d == LEFT)
      p->x -= distance;
    else if (d == RIGHT)
      p->x += distance;
  }
  else
  {
    if (d == UP)
      p->y += distance;
    else if (d == DOWN)
      p->y -= distance;
  }
}

bool intersect(cpiece p1, cpiece p2)
{
  if (get_x(p1) == get_x(p2) && get_y(p1) == get_y(p2))
    return true;
  if (is_horizontal(p1)){
    if (is_horizontal(p2)){
      if (get_y(p1) != get_y(p2))
  	return false;
      if ( (((get_x(p1)+get_width(p1)) > get_x(p2)) && (get_x(p1) < (get_x(p2)+get_width(p2))))  ||  (((get_x(p2)+get_width(p2)) > get_x(p1)) && (get_x(p2) < (get_x(p1)+get_width(p1)))) )
  	return true;
      return false;
    }
    if ( (get_y(p1) < get_y(p2))  ||  (get_y(p1) > (get_y(p2)+get_height(p2))) )
      return false;
    if ( (get_x(p1) <= get_x(p2)) && (get_x(p1)+get_width(p1) > get_x(p2)) )
      return true;
    return false;
  }
  if (!is_horizontal(p2)){
    if (get_x(p1) != get_x(p2))
      return false;
    if ( (((get_y(p1)+get_height(p1)) > get_y(p2)) && (get_y(p1) < (get_y(p2)+get_height(p2))))  ||  (((get_y(p2)+get_height(p2)) > get_y(p1)) && (get_y(p2) < (get_y(p1)+get_height(p1)))) )
  	return true;
    return false;
  }
  if ( (get_y(p2) < get_y(p1))  ||  (get_y(p2) > (get_y(p1)+get_height(p1))) )
    return false;
  if ( (get_x(p2) <= get_x(p1)) && (get_x(p2)+get_width(p2) > get_x(p1)) )
    return true;
  return false;
}
  
int get_x(cpiece p){
  return p->x;
}

int get_y(cpiece p){
  return p->y;
}

int get_height(cpiece p){
  if (is_horizontal(p))
      return 1;
  else{
    if (p->small == true)
      return 2;
    else
      return 3;
  }
}

int get_width(cpiece p){
  if (!is_horizontal(p))
    return 1;
  else{
    if (p->small == true)
      return 2;
    else
      return 3;
  }
}

bool is_horizontal(cpiece p){
  return p->horizontal;
}


