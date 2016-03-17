#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "piece.h"


struct piece_s
{
  int x;
  int y;
  int width;
  int height;
  bool move_x;
  bool move_y;
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
  if (horizontal){
    p->width = 3;
    p->height = 1;
    p->move_x = true;
    p->move_y = false;
    if (small)
      p->width -= 1;
  }
  else{
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
    if (d == LEFT)
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
    if ( (get_y(p1) < get_y(p2))  ||  (get_y(p1) > (get_y(p2)+get_height(p2)-1)) )
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
  if ( (get_y(p2) < get_y(p1))  ||  (get_y(p2) > (get_y(p1)+get_height(p1)-1)) )
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
  return p->height;
}

int get_width(cpiece p){
  return p->width;
}

bool is_horizontal(cpiece p){
  return can_move_x(p);
}

bool can_move_x(cpiece p){
  return p->move_x;
}

bool can_move_y(cpiece p){
  return p->move_y;
}

piece new_piece(int x, int y, int width, int height, bool move_x, bool move_y){
  piece p = (piece) malloc(sizeof(*p));
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


