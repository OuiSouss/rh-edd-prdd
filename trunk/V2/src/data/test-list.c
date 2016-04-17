#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "list.h"

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

//This function is used instead the argument "delete" in the function delete_list, because the integer we are working with are not allocated with malloc, so they don't have to be freed with a function.
void noth(void *e)
{
  return;
}

typedef void(*useless)(void*);
useless nothing=noth;

int tab[3]={1,2,3};
list l1;
list l2;

/**
 *@brief create exemples of lists.
 **/
void set_up()
{
  l1=create_list(tab,NULL);
  l2=create_list(tab+1,l1);
}

/**
 *@brief delete a list.
 *@param l the list to delete.
 **/
void tear_down(list l)
{
  delete_list(l2,nothing);
}


bool test_create()
{
   printf("Test of the function \"create_list\".\n");
   bool result=true;
   printf("Creation...\n");
   set_up();
   printf("Check if the lists were correctly created. One is a simple list creation, and another is a first insered list creation.\n");
   result= result && test_equality_int(tab[0],(int)*(int *)get_data(l1),"create_list");
   result= result && test_equality_null(next(l1),"create_list");
   result= result && test_equality_int(tab[1],(int)*(int *)get_data(l2),"create_list");
   result= result && test_equality_int(tab[0],(int)*(int *)get_data(next(l2)),"create_list");
   printf("Checked.\n");
   printf("Freeing memory...\n");
   tear_down(l2);
   printf("Done %s.\n\n",result?"with no error":"with errors");
   return result;
}

bool test_add_after()
{
 printf("Test of the function \"create_list\".\n");
 bool result=true;
 printf("Creation...\n");
 set_up();
 printf("Try to add a list after an already created list, giving data.\n");
 add_after(l1,tab+2);
 printf("Check if the element was correctly added.\n");
 result=result && test_equality_int(tab[2],(int)*(int *)get_data(next(next(l2))),"add_after");
 printf("Checked.\n");
 printf("Freeing memory...\n");
 tear_down(l2);
 printf("Done %s.\n\n",result?"with no error":"with errors");
 return result;
}

bool test_erase_first()
{
  printf("Test of the function \"erase_first\".\n");
  bool result=true;
  printf("Creation...\n");
  set_up();
  printf("Try to erase the lists.\n");
  list l=l2;
  while(!empty_list(l))
    {
      list tmp=next(l);
      erase_first(l,nothing);
      l=tmp;
    }
  result= result && test_equality_null(l,"erase_first");
  printf("Done %s.\n\n",result?"with no error":"with errors");
  return result;
}

bool test_erase_after()
{
  printf("Test of the function \"erase_first\".\n");
  bool result=true;
  printf("Creation...\n");
  set_up();
  printf("Try to erase the second list.\n");
  erase_after(l2,nothing);
  result= result && test_equality_null(next(l2),"erase_after");
  printf("Freeing memory...\n");
  tear_down(l2);
  printf("Done %s.\n\n",result?"with no error":"with errors");
  return result;
}

int main()
{
  printf("Test of functions in the file list.c.\n\n");
  bool result=true;
  result=result && test_create();
  result=result && test_add_after();
  result=result && test_erase_first();
  result=result && test_erase_after();
  if(result)
    {
      printf("All tests succedeed : list.c has no problem!\n\n");
      return EXIT_SUCCESS;
    }
  else
    {
      printf("Error : there are still problems in list.c!\n\n");
      return EXIT_FAILURE;
    }
}

