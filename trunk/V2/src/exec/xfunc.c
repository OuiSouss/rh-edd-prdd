#include <stdlib.h>

#include <error_flags>

void* xmalloc(const unsigned int size, int* status)
{
  void* ptr = NULL;
  if (size != 0)
    ptr = malloc(size);
  if (!ptr)
    *status = ALLOC_ERROR;
  return ptr;
}

void xfree(void** ptr)
{
  if (*ptr)
    free(*ptr);
  *ptr = NULL;
}
