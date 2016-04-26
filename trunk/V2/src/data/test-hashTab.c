#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "list.h"
#include "hashTab.h"

#define LENGTH 10
#define NB_ELEMENTS_ADDED 20

/**
 *@brief test if boolean value is equal to expected. If not, displays an error message indicating expected, value and name of the tested function.
 *@param testF is the name of the tested function.
 *@return true if expected==value.
 */
bool test_equality_bool(bool expected, bool value, char *testF)
{
  if(expected!=value)
    {
      fprintf(stderr,"ERROR: expected %d is different to value %d in tested function: %s!\n",expected,value,testF);
    }
  return expected==value;
}

/**
 *@brief test if integer value is equal to expected. If not, displays an error message indicating expected, value and name of the tested function.
 *@param testF is the name of the tested function.
 *@return true if expected==value.
 */
bool test_equality_int(int expected, int value, char *testF)
{
  if(expected!=value)
    {
      fprintf(stderr,"ERROR: expected %d is different to value %d in tested function: %s!\n",expected,value,testF);
    }
  return expected==value;
}

/**
 *@brief test if pointer is equal to NULL. If not, displays an error message indicating the tested function.
 *@param testF is the name of the tested function.
 *@return true if p==NULL.
 */
bool test_equality_null(void *p, char *testF)
{
  if(p!=NULL)
    {
      fprintf(stderr,"ERROR: pointer p is not NULL!\n");
    }
  return p==NULL;
}

/*

Elements : [ 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 610, 987, 1597, 2584, 4181, 6765]

HashTab:
0| 610
1| 4181 <-21 <-1
2| 2
3| 233 <-13 <-3
4| 2584 <-144 <-34
5| 6765 <-55 <-5
6| 
7| 1597 <-987 <-377
8| 8
9| 89

 */

/*elements : [1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 610, 987, 1597, 2584, 4181, 6765]
 */
int elements[NB_ELEMENTS_ADDED];
list t[LENGTH];

/**
 *@brief create an integer array wihch will be used to create list and a list array that will be compared wihth the hashTab's one (see exemples above).
 **/
void set_up()
{
  elements[0]=1;
  elements[1]=1;
  for(int i=2;i<NB_ELEMENTS_ADDED;i++)
    elements[i]=elements[i-2]+elements[i-1];
  for(int i=0;i<LENGTH;i++)
    t[i]=create_list(NULL,NULL);
  t[0]=create_list(elements+14,NULL);
  t[1]=create_list(elements+1,NULL);
  t[1]=create_list(elements+7,t[1]);
  t[1]=create_list(elements+18,t[1]);
  t[2]=create_list(elements+2,NULL);
  t[3]=create_list(elements+3,NULL);
  t[3]=create_list(elements+6,t[3]);
  t[3]=create_list(elements+12,t[3]);
  t[4]=create_list(elements+8,NULL);
  t[4]=create_list(elements+11,t[4]);
  t[4]=create_list(elements+17,t[4]);
  t[5]=create_list(elements+4,NULL);
  t[5]=create_list(elements+9,t[5]);
  t[5]=create_list(elements+19,t[5]);
  t[7]=create_list(elements+13,NULL);
  t[7]=create_list(elements+15,t[7]);
  t[7]=create_list(elements+16,t[7]);
  t[8]=create_list(elements+5,NULL);
  t[9]=create_list(elements+10,NULL);
}
//This function is used instead the argument "delete" in the function delete_list, because the integer we are working with are not allocated with malloc, so they don't have to be freed with a function.
void d(void *p)
{
  p=NULL;
}

typedef void(*delete)(void*);
delete del=d;

/**
 *@brief delete all the lists of the list array, created with the function above.
 **/
void tear_down()
{
  for(int i=0;i<LENGTH;i++)
    delete_list(t[i],del);
}

/**
 *@brief exemple of a hash function.
 *@param a an integer, a hashTab's element.
 *@return the indice of the hashTab where the element has to be put.
 **/
void *hashF(void *p_a)
{
  int *p=(int *)p_a;
  int i=*(p)%LENGTH;
  int *p_i=&i;
  p_i=(void *)p_i;
  return p_i;
}

hashFunction hf=&hashF;

/**
 *@brief test if two pointers point toward the same value.
 *@param p1 is the first pointer.
 *@param p2 is the second pointer.
 *@return true if *p1==*p2.
 **/
bool equalsF(void *p1,void *p2)
{
  if(p1==NULL && p2==NULL)
    return true;
  if(p1==NULL || p2==NULL)
    return false;
  //In this file, we are working with integers, so we can cast these pointers into integer pointers.
  int *p_1=(int *)p1;
  int *p_2=(int *)p2;
  return *p_1==*p_2;
}

equalsFunction ef=&equalsF;


void affiche(hashTab h)
{
  list l;
  for(int i=0;i<get_length(h);i++)
    {
      printf("%d : ",i);
      l=get_tab_index(h,i);
      while(l!=NULL)
	{
	  printf("%d",(int)*(int*)get_data(l));
	  if(has_next(l))
	    printf(" -> ");
	  l=next(l);
	}
      printf("\n");
    }
}

/**
 *@brief test if a hashTab is correctly created.
 *@return true if the function "create_hash_tab" has no error.
 **/
bool test_create()
{
  printf("Test of the function \"create_hash_tab\".\n");
  bool result=true;
  printf("Creation...\n");
  hashTab h=create_hash_tab(LENGTH,hf);
  affiche(h);
  printf("Checking...\n");
  result= result && test_equality_int(LENGTH,get_length(h),"create_hash_tab length");
  for(int i=0;i<get_length(h);i++)
    result= result && test_equality_null(get_tab_index(h,i),"create_hash_tab tab");
  printf("Freeing memory...\n");
  destroy_hash_tab(h,del);
  printf("Done %s.\n\n",result?"with no error":"with errors");
  return result;  
}

/**
 *@brief test if an element is correctly added into a hashTab.
 *@return true if the function "add_hash_tab" has no error.
 **/
bool test_add()
{
  printf("Test of the function \"add_hash_tab\".\n");
  bool result=true;
  printf("Creation...\n");
  set_up();
  hashTab h=create_hash_tab(LENGTH,hf);
  printf("Adding all the elements...\n");
  for(int i=0;i<NB_ELEMENTS_ADDED;i++)
    {
      printf("\tElement number %d : %d",i,elements[i]);
      add_hash_tab(h,elements+i,ef);
      printf("\t\tAdded.\n");
    }
  affiche(h);
  printf("Check if the list array of the hashTab was correctly done : \n");
  for(int i=0;i<LENGTH;i++)
    {
      printf("\tList number %d.",i);
      list lt=t[i];
      list lh=get_tab_index(h,i);
      while(!empty_list(lh))
	{
	  result=result && test_equality_bool(true,ef(get_data(lt),get_data(lh)),"add_hash_tab");
	  lt=next(lt);
	  lh=next(lh);
	}
      printf("\t\tChecked.\n");
    }
  printf("Freeing memory...\n");
  destroy_hash_tab(h,del);
  tear_down();
  printf("Done %s.\n\n",result?"with no error":"with errors");
  return result;
}

/**
 *@brief test if an element is correctly returned from a hashTab.
 *@return true if the function "get_hash_tab" has no error.
 **/
bool test_get()
{
  printf("Test of the function \"get_hash_tab\".\n");
  bool result=true;
  printf("Creation...\n");
  set_up();
  hashTab h=create_hash_tab(LENGTH,hf);
  printf("Adding all the elements...\n");
  for(int i=0;i<NB_ELEMENTS_ADDED;i++)
    {
      printf("\tElement number %d : %d",i,elements[i]);
      add_hash_tab(h,elements+i,ef);
      printf("\tAdded.\n");
    }
  printf("Check the return of get_hash_tab for some keys of the hashTab.\n");
  list lt=t[0];
  result=result && test_equality_bool(true,ef(get_data(lt),get_hash_tab(h,get_data(lt),ef)),"get_hash_tab");
  lt=next(next(t[3]));
  result=result && test_equality_bool(true,ef(get_data(lt),get_hash_tab(h,get_data(lt),ef)),"get_hash_tab");
  test_equality_null(get_tab_index(h,6),"get_hash_tab");
  printf("Freeing memory...\n");
  destroy_hash_tab(h,del);
  tear_down();
  printf("Done %s.\n\n",result?"with no error":"with errors");
  return result;
}

/**
 *@brief test if an element is correctly deleted from a hashTab.
 *@return true if the function "delete_hash_tab" has no error.
 **/
bool test_delete()
{
  printf("Test of the function \"delete_hash_tab\".\n");
  bool result=true;
  printf("Creation...\n");
  set_up();
  hashTab h=create_hash_tab(LENGTH,hf);
  printf("Adding all the elements...\n");
  for(int i=0;i<NB_ELEMENTS_ADDED;i++)
    {
      printf("\tElement number %d : %d",i,elements[i]);
      add_hash_tab(h,elements+i,ef);
      printf("\tAdded.\n");
    }
  printf("Trying to delete some elements...\n");
  int e1=1,e2=2,e3=6;
  //p_e1, p_e2 and p_e3 are pointers toward e1, e2 and e3. They will be used in the functions delete_hash_tab and get_hash_tab.
  int *p_e1=&e1,*p_e2=&e2,*p_e3=&e3;
  delete_hash_tab(h,p_e1,ef,del);
  delete_hash_tab(h,p_e2,ef,del);
  delete_hash_tab(h,p_e3,ef,del);
  affiche(h);
  printf("Checking if the elements were correctly deleted...\n");
  result=result && test_equality_null(get_hash_tab(h,p_e1,ef),"delete_hash_tab get_hash_tab");
  result=result && test_equality_null(get_hash_tab(h,p_e2,ef),"delete_hash_tab get_hash_tab");
  result=result && test_equality_null(get_hash_tab(h,p_e3,ef),"delete_hash_tab get_hash_tab");
  printf("Freeing memory...\n");
  destroy_hash_tab(h,del);
  tear_down();
  printf("Done %s.\n\n",result?"with no error":"with errors");
  return result;
}


int main()
{
  printf("Test of functions in the file hashTab.c.\n\n");
  bool result=true;
  result=result && test_create();
  result=result && test_add();
  result=result && test_get();
  result=result && test_delete();
  if(result)
    {
      printf("All tests succedeed : hashTab.c has no problem!\n\n");
      return EXIT_SUCCESS;
    }
  else
    {
      printf("Error : there are still problems in hashTab.c!\n\n");
      return EXIT_FAILURE;
    }
}
