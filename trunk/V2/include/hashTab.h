#ifndef HASHTAB_H
#define HASHTAB_H

/**
 *@file hashtab.h
 *
 *@brief A hashTab is a data structure allowing to map keys to values, using a hash function to compute an index into an array of slots.
 *
 **/

/**
 *@struct hashTab_s
 *@brief A hashTab is a data structure allowing to map keys to values, using a hash function to compute an index into an array of slots.
 *
 * A hashTab is characterized by an list array of slots indexing its keys, and a hash function allowing to put values into the array.
 * hashTab is a pointer to the structure that describes a hashTab.
 *
 * chashTab is a pointer toward a constant hashTab.
 * This means that it is not possible to modifiy the hashTab through this pointer.
 *
 *
 **/
typedef struct hashTab_s* hashTab;
typedef const struct hashTab_s* chashTab;

/**
 *@brief A hashFunction is a function which will index elements into a list array.
 **/
typedef void*(* hashFunction)(void *);

/**
 *@brief An equalsFunction is a function which checks if two elements are the same through two pointers, and returns true in this case.
 **/
typedef bool(* equalsFunction)(void *, void *);

/**
 *@brief An indexFunction is a function which returns a pointer toward a table at a specific index.
 **/
typedef void*(* indexFunction)(void *, int);

/**
 *@brief Creates a new hashTab.
 *@param lenght is the length of the list array indexing the keys (or the number of slots in the array).
 *@param f is the hash function used to index the keys into the array.
 *@return a pointer toward the generated hashTab.
 **/
hashTab create_hash_tab(int n, hashFunction f);

/**
 *@brief Destroys the hashTab and frees allocated memory.
 *@param h the hashTab to destroy.
 *@param delete is a function wich correctly frees memory from the type used in the lists. It has to do nothing if the used type was not allocated with malloc.
 **/
void destroy_hash_tab(hashTab h,void (*delete)(void *));

/**
 *@brief Add the element e into the hashTab h, if it wasn't added before.
 *@param h the hashTab to modify.
 *@param e a pointer toward the element to add.
 *@param f is a function used to check the equality between two pointed elements.
 **/
void add_hash_tab(hashTab h,void* e,equalsFunction f);

/**
 *@brief Delete the element e of the hashTab h, if it exists.
 *@param h the hashTab to modify.
 *@param e a pointer toward the element to delete.
 *@param f is a function used to check the equality between two pointed elements.
 *@param delete is a function wich correctly frees memory from the type used in the lists. It has to do nothing if the used type was not allocated with malloc.
 **/
void delete_hash_tab(hashTab h, void* e,equalsFunction f,void (*delete)(void *));

/**
 *@brief Gives the pointer of the element e, if it exists.
 *@param h the constant hashTab where the element e is researched.
 *@param e the researched element.
 *@param f is a function used to check the equality between two pointed elements.
 *@return a pointer toward the element of a list, or NULL if it does not exist.
 **/
void* get_hash_tab(chashTab h, void* e,equalsFunction f);

/**
 *@brief Returns the length of the hashTab member "tab".
 *@param h the hashTab with the asked length.
 **/
int get_length(chashTab h);

/**
 *@brief Returns a pointer toward the hashTab member "tab" at the good index.
 *@param h the hashTab with the asked tab.
 **/
void* get_tab_index(hashTab h,int index);

#endif
