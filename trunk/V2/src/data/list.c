#include "list.h"
#include <stdlib.h>
#include <stdio.h>

struct list_s{
  void* data;
  struct list_s* next;
};

list create_list(void* data, list n_list)
{
  list _list = malloc (sizeof(*_list));
  if(_list==NULL)
  {
      fprintf(stderr,"Error of memory allocation!\n");
      exit(EXIT_FAILURE);
  }
  _list->data = data;
  _list->next = n_list; 
  return _list;
}

void* get_data(list _list)
{
  return _list->data;
}

list next(list _list)
{
  return _list->next;
}

bool has_next(list _list)
{
  return _list->next!=NULL;
}

bool empty_list(list _list)
{
  return _list==NULL;
}

void add_after(list _list, void* data)
{
  while(!(empty_list(_list)) && has_next(_list))
    _list = _list->next;
  if (_list)
    _list->next = create_list(data, NULL);
}

void erase_first(list _list,void (*delete)(void *))
{
  if (!has_next(_list)){
    free(_list);
    delete(get_data(_list));
  }
  else{
    list first = _list ;
    _list = _list->next;
    delete(get_data(first));
    free(first);
  }
}

void erase_after(list _list, void(*delete)(void *))
{
  if(empty_list(_list) || !has_next(_list))
    return;
  list tmp=next(_list);
  _list->next=next(tmp);
  delete(get_data(tmp));
  free(tmp);
}
  

void delete_list(list _list, void (*delete)(void *))
{
  while(!empty_list(_list))
  {
    delete(_list->data);
    list prev = _list;
    _list = _list->next;
    free(prev);
  }
}
