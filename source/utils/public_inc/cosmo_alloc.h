#ifndef COSMO_ALLOC_H
#define COSMO_ALLOC_H

#include <stddef.h>

/**
 * @brief Allocates a block of memory of the specified size.
 * @param[in] size The size of the memory block to allocate.
 * @return A pointer to the allocated memory block, or NULL if the allocation fails.
 */
void* cosmo_malloc(size_t size);

/**
 * @brief Frees the memory pointed to by the given pointer.
 * @param ptr A pointer to the memory to be freed.
 */
void cosmo_free(void* ptr);

#endif // COSMO_ALLOC_H
