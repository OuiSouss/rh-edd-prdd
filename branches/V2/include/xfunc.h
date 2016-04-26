#ifndef _X_FUNC_H
# define _X_FUNC_H

/**
 * @file xfunc.h
 * @brief Header referring to useful safe calls.
 */

/**
 * @fn void* xmalloc (const unsigned int size, int* status)
 * @brief Wrapper encapsulating malloc system calls.
 * @param[in] size The size of the area to allocate.
 * @param[in,out] status The field used to store the error flag if needed.
 * @return A pointer at the start of the area allocated when a call to malloc is successfull,
 * NULL when the calls fails or the size was 0.
 */
void* xmalloc(const unsigned int size, int* status);

/**
 * @fn void xfree (void** ptr)
 * @brief Wrapped encapsulating free system calls.
 * @param[in, out] ptr A pointer pointing to the pointer of the area to free.
 * @post No operation is performed if *ptr equals NULL, otherwise a call to free
 * is done and *ptr is then set to NULL.
 */
void xfree(void** ptr);

#endif /* _X_FUNC_H */
