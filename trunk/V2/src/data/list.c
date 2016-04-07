#include "list.h"
#include <stdlib.h>

struct list_s{
  void* data;
  struct list_s* next;
};

list create_list(void* data, list n_list)
{
  list list = malloc (sizeof(*list));
  if(list!=NULL)
  {
    list->data = data;
    list->next = n_list; 
  }
  return list;
}

void* get_data(list list)
{
  return list->data;
}

list next(list list)
{
  return list->next;
}

bool has_next(list list)
{
  return list->next!=NULL;
}

bool empty_list(list list)
{
  return list==NULL;
}

void add_after(list list, void* data)
{
  while(!(empty_list(list)) && has_next(list))
    list = list->next;
  if (list)
    list->next = create_list(data, NULL);
}

void erase_first(list list)
{
  
}

void erase_after(list list)
{
  
}
list prev =NULL;
void delete_list(list list, void (*delete)(void *))
{
  while(!empty_list(list))
  {
    delete(list->data);
    prev = list;
    list = list->next;
    free(prev);
  }
}
