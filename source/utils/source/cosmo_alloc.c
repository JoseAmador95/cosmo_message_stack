#include "cosmo_alloc.h"

#include <stdlib.h>

void* cosmo_malloc(size_t size)
{
    return malloc(size);
}

void cosmo_free(void* ptr)
{
    free(ptr);
}