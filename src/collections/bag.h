#pragma once

typedef struct Bag *Bag;

Bag Bag_new(int elemSize);
int Bag_Add(Bag Bag, void *data);
void Bag_Get(Bag Bag, int index, void *dest);
void Bag_Remove(Bag Bag, int index);
int Bag_Count(Bag Bag);
int Bag_ToIndexArray(Bag Bag, void *array);
int Bag_ToArray(Bag Bag, void *array);
void Bag_Dispose(Bag Bag);
void *Bag_Data(Bag bag);