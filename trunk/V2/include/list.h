#ifndef _LIST_H_
#define _LIST_H_
#include <stdbool.h>

typedef struct list_s* list;

list create_list(void* data, list n_list);
void* get_data(list list);
list next(list list);
bool has_next(list list);
bool empty_list(list list);
void add_after(list list, void* data);
void erase_first(list list);
void erase_after(list list);
void delete_list(list list, void(*delete)(void *));

#endif
