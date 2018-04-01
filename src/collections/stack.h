#pragma once
#include <stddef.h>
#include <stdbool.h>

typedef struct Stack *Stack;

Stack Stack_new(int capacity, size_t elemSize);
bool Stack_Push(Stack stack, void *elem);
bool Stack_Pop(Stack stack, void *elem);
bool Stack_Peek(Stack stack, void* elem);
void Stack_Rotate(Stack stack, int desp);
int Stack_Count(Stack stack);
void Stack_ToArray(Stack stack, void *array);
void Stack_Dispose(Stack stack);