#pragma once
#include <stdbool.h>
#include <stddef.h>

typedef struct List List;

List *List_Create(size_t size);
void List_Dispose(List *list);
void List_Add(List *list, const void *e);
void List_Insert(List *list, size_t idx, const void *e);
bool List_Get(const List *list, size_t idx, void *dest);
bool List_RemoveIndex(List *list, size_t idx);
bool List_Remove(List *list, const void *e);
bool List_RemoveLast(List *list, const void *e, int (*equals)(const void *a, const void *b));
size_t List_Count(const List *list);
bool List_IsEmpty(const List *list);
bool List_Contains(const List *list, const void *e);
void List_Clear(List *list);
int List_ToArray(const List *list, void **array);