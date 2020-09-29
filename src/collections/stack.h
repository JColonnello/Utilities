#pragma once
#include <stddef.h>
#include <stdbool.h>

typedef struct Stack Stack;

Stack *Stack_Create(size_t capacity, size_t elemSize);
bool Stack_Push(Stack *stack, void *elem);
bool Stack_Pop(Stack *stack, void *elem);
bool Stack_Peek(const Stack *stack, void* elem);
void Stack_Rotate(Stack *stack, int desp);
int Stack_Count(const Stack *stack);
void Stack_ToArray(const Stack *stack, void *array);
void Stack_Dispose(Stack *stack);