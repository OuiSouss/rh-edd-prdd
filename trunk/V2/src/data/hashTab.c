#include <stdio.h>
#include <stdlib.h>

#include "list.h"
#include "hashTab.h"

struct hashTab_s
{
  list *tab;
  int length;
  hashFunction hf;
};


hashTab create_hash_tab(int n, hashFunction f)
{
  hashTab tmp1;
  tmp1=(hashTab)malloc(sizeof(*tmp1));
  //Verification of the memory allocation.
  if(tmp1==NULL)
    {
      fprintf(stderr,"Error of memory allocation!\n");
      exit(EXIT_FAILURE);
    }
  list *tmp2;
  tmp2=(list *)malloc(n*sizeof(*tmp2));
  //Verification of the memory allocation.
  if(tmp2==NULL)
    {
      fprintf(stderr,"Error of memory allocation!\n");
      exit(EXIT_FAILURE);
    }
  for(int i=0;i<n;i++)
    tmp2[i]=NULL;
  tmp1->tab=tmp2;
  tmp1->length=n;
  tmp1->hf=f;
  return tmp1;
}

void destroy_hash_tab(hashTab h,void(*delete)(void *))
{
  int n=h->length;
  //Free each element of the list array.
  for(int i=0;i<n;i++)
      delete_list(h->tab[i],delete);
  free(h->tab);
  free(h);
}

void add_hash_tab(hashTab h, void* e,equalsFunction ef)
{
  hashFunction f=h->hf;
  //Find where to put the element thanks to the hash function. p_i is a pointer toward the index choosen.
  int *p_i=(*f)(e);
  int i=*p_i;
  //Check if a list has never been created. and if there's not already the element in the hashTab.
  list l=h->tab[i];
  bool check=false;
  if(empty_list(l))
    {
      h->tab[i]=create_list(e,NULL);
    }
  //If a a list has ever been created, check if the new added element is not already in the hashTab, and if not, add it. 
  else
    {
      void* data;
      while(!empty_list(l))
	{
	  data=get_data(l);
	  //Check if the elements pointed by data and e are the same.
	  if(ef(data,e))
	    check=true;
	  l=next(l);
	}
      if(!check)
	{
	  list tmp=create_list(e,h->tab[i]);
	  h->tab[i]=tmp;
	}
    }
}

void delete_hash_tab(hashTab h, void* e,equalsFunction ef,void(*delete)(void *))
{
  hashFunction f=h->hf;
  //Find where was the element put thanks to the hash function. p_i is a pointer toward the index choosen.
  int *p_i=(*f)(e);
  int i=*p_i;
  /*list *l=&(h->tab[i]);*/
  //If l is NULL, the element cannot have been add before, so the function stops.
  if(empty_list(h->tab[i]))
    return;
  //Check if the first element of the list is the researched one.
  void *data=get_data(h->tab[i]);
  if(ef(data,e))
    erase_first(h->tab[i],delete);
  //Run through the list to check if the researched element exists, and if yes, deletes it.
  else
    {
      int j=0;
	while(has_next(h->tab[i]))
	  {
	    data=get_data(next(h->tab[i]));
	    //Check if the elements pointed by data and e are the same.
	    if(ef(data,e))
	      {
		erase_after(h->tab[i],delete);
		break;
	      }
	    else
	      h->tab[i]=next(h->tab[i]);
	    j++;
	  }
    }
}

void* get_hash_tab(chashTab h, void* e,equalsFunction ef)
{
  hashFunction f=h->hf;
  //Find where to put the element thanks to the hash function. p_i is a pointer toward the index choosen.
  int *p_i=(*f)(e);
  int i=*p_i;
  list l=h->tab[i];
  //If l is NULL, the element cannot have been add before, so the function stops.
  if(empty_list(l))
    return NULL;
  //Check if the first element of the list is the researched one.
  void *data=get_data(l);
  if(!empty_list(l) && ef(data,e))
    return get_data(l);
  //Run through the list to check if the researched element exists, and if yes, returns it.
  while(!empty_list(l))
    {
      data=get_data(l);
      //Check if the elements pointed by data and e are the same.
      if(ef(data,e))
	return get_data(l);
      l=next(l);
    }
  //Return NULL if the element was not found.
  return NULL;
}

int get_length(hashTab h)
{
  return h->length;
}

void* get_tab_index(hashTab h,int index)
{
  return h->tab[index];
}
