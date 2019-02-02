#pragma once
#include <stddef.h>

typedef struct Pool Pool;

Pool *Pool_Create(size_t elemSize);
int Pool_Add(Pool *pool, void *data);
void Pool_Get(Pool *pool, int index, void *dest);
void Pool_Remove(Pool *pool, int index);
int Pool_Count(Pool *pool);
int Pool_ToIndexArray(Pool *pool, int *array);
int Pool_ToArray(Pool *pool, void *array);
void Pool_Dispose(Pool *pool);
void *Pool_Data(Pool *pool);