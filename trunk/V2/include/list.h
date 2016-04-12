#ifndef _LIST_H_
#define _LIST_H_
#include <stdbool.h>

/**
 * @file list.h
 *
 * @brief This file describe all functions to maniputate a simple linked list. 
 *
 **/

/**
 * @struct list_s
 * @brief A simple linked list is described by a data and a pointeur to the next element of the list.
 **/

typedef struct list_s* list;

/**
 * @brief Create a new simple linked list.Create_list can be used like a function add_first because n_list can be a list first.
 * @param Data is in generic because we don't know the type of data we will put in the list.
 * @param n_list is NULL if no list exist first but it can point on a list first.
 * @return a pointer toward the generated list.
 **/
list create_list(void* data, list n_list);

/**
 * @brief Return the data pointed by the list currently.
 * @param Pointer on the list
 **/

void* get_data(list _list);

/**
 * @brief Return the pointer next of the current list
 * @param Pointer on a list
 **/
list next(list _list);

/**
 * @brief Test if the list in parameter has a pointer on a valid instance
 * @param Pointer on a list
 * @return true if the list has a next element
 **/ 
bool has_next(list _list);

/**
 * @brief Test if the list is empty.
 * @param Pointer on a list
 * @return true if the list has no element 
 **/
bool empty_list(list _list);

/**
 * @brief Permit to add a data after the current position on the list.
 * @param Pointer on a list
 * @param an element data to add in the list
 **/
void add_after(list _list, void* data);

/**
 * @brief Permit to erase the first element in the list.
 * @param Pointer on a list
 * @return Pointer on the modified list
 **/
list erase_first(list _list);

/**
 * @brief Permit to erase a element after a position on the list.
 * @param Pointer on a list
 * @param index position on a list where the next need to be erase
 * @return Pointer on the modified list
 **/
list erase_after(list _list, int index);

/**
 * @brief Permit to delete all the list
 * @param Pointer on a list
 * @param Function pointer which permit to erase every type of data
 **/
void delete_list(list _list, void(*delete)(void *));

#endif
