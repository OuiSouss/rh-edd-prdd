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
  if(_list!=NULL)
  {
    _list->data = data;
    _list->next = n_list; 
  }
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

list erase_first(list _list)
{
  if (!has_next(_list)){
    free(_list);
    return NULL;
  }
  list first = _list ;
  _list = _list->next;
  free(first);
  return _list;
  
}

list erase_after(list _list, int index)
{
  if (index==0)
    return erase_first(_list);
  list tmp = _list;
  int current_index = 0;
  while((!empty_list(tmp)) && current_index<=index)
  {
    tmp = next(tmp);
    current_index++;
  }
  if(empty_list(tmp))
    printf("Your index in parameters is out of length list");
    return _list;
  if(!has_next(tmp))
     return _list;
  list next_to_erase = next(tmp);
  tmp->next = next_to_erase->next;
  free(next_to_erase);    
  return _list;
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
