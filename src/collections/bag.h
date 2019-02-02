#pragma once
#include <stddef.h>

typedef struct Bag Bag;

Bag *Bag_Create(size_t elemSize);
int Bag_Add(Bag *bag, void *data);
void Bag_Get(Bag *bag, int index, void *dest);
void Bag_Remove(Bag *bag, int index);
int Bag_Count(Bag *bag);
int Bag_ToIndexArray(Bag *bag, int *array);
int Bag_ToArray(Bag *bag, void *array);
void Bag_Dispose(Bag *bag);
void *Bag_Data(Bag *bag);