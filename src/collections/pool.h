#pragma once
#include <stddef.h>

typedef struct Pool Pool;
typedef int Handle;

Pool *Pool_Create(size_t elemSize);
Handle Pool_Add(Pool *pool, const void *data);
void Pool_Get(Pool *pool, Handle index, void *dest);
void *Pool_GetRef(Pool *pool, Handle index);
void Pool_Remove(Pool *pool, Handle index);
int Pool_Count(Pool *pool);
int Pool_ToIndexArray(Pool *pool, Handle *array);
int Pool_ToArray(Pool *pool, void *array);
void Pool_Dispose(Pool *pool);
void *Pool_Data(Pool *pool);