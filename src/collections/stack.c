#include "Stack.h"
#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include <string.h>

#define DEFAULT_CAPACITY 32
#define STACK_SIZE(stack) stack->count * stack->elemSize
#define STACK_END(stack) stack->data + STACK_SIZE(stack)

struct Stack
{
	bool expandible;
	int capacity;
	int count;
	size_t elemSize;
	char *data;
};

Stack Stack_new(int capacity, size_t elemSize)
{
	Stack stack = malloc(sizeof(struct Stack));

	if(stack == NULL)
		return NULL;

	if(capacity < 0)
	{
		printf("Negative capacity for Stack\n");
		return NULL;
	}
	else if(capacity == 0)
	{
		capacity = DEFAULT_CAPACITY;
		stack->expandible = true;
	}
	else
	{
		stack->expandible = false;
	}		

	stack->data = malloc(capacity * elemSize);
	if(stack->data == NULL)
		return NULL;
	stack->capacity = capacity;
	stack->count = 0;
	stack->elemSize = elemSize;

	return stack;
}

bool Stack_Push(Stack stack, void *elem)
{
	if(stack->count >= stack->capacity)
	{
		if(stack->expandible)
		{
			void *newDataBlock = (Stack)malloc(STACK_SIZE(stack) * 2);
			if(newDataBlock != NULL)
			{
				Stack_ToArray(stack, newDataBlock);
				free(stack->data);
				stack->capacity *= 2;
				stack->data = newDataBlock;
			}
			else
				return false;
		}
		else
			return false;
	}
	memcpy(STACK_END(stack), elem, stack->elemSize);
	stack->count++;

	return true;
}

bool Stack_Pop(Stack stack, void *elem)
{
	if(stack->count <= 0)
		return false;

	if(elem != NULL)
		memcpy(elem, STACK_END(stack), stack->elemSize);
	stack->count--;
	return true;
}

bool Stack_Peek(Stack stack, void* elem)
{
	if(stack->count <= 0)
		return false;

	memcpy(elem, STACK_END(stack), stack->elemSize);
	return true;
}

void Stack_Rotate(Stack stack, int desp)
{
	if(stack->count <= 1)
		return;

	int division = (stack->count - desp) % stack->count;
	if(division == 0)
		return;

	size_t min, smallSize, bigSize;
	if(division < (stack->count - division))
	{
		min = division;
		smallSize = division * stack->elemSize;
		bigSize = (stack->count - division) * stack->elemSize;
	}
	else
	{
		min = (stack->count - division);
		smallSize = (stack->count - division) * stack->elemSize;
		bigSize = division * stack->elemSize;
	}

	void *temp;
	if(stack->capacity >= (stack->count + min))
		temp = STACK_END(stack);
	else
	{
		temp = alloca(min * stack->elemSize);
		if(temp == NULL)
			return;
	}

	if(division == min)
	{
		memmove(temp, stack->data, smallSize);
		memmove(stack->data, stack->data + smallSize, bigSize);
		memmove(stack->data + bigSize, temp, smallSize);
	}
	else
	{
		memmove(temp, stack->data + bigSize, smallSize);
		memmove(stack->data + bigSize, stack->data, bigSize);
		memmove(stack->data, temp, smallSize);
	}
}

int Stack_Count(Stack stack)
{
	return stack->count;
}

void Stack_ToArray(Stack stack, void *array)
{
	if(stack->count <= 0)
		return;
	memcpy(array, stack->data, STACK_SIZE(stack));
}

void Stack_Dispose(Stack stack)
{
	free(stack->data);
	free(stack);
}