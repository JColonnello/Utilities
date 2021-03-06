#include <collections/stack.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

#define DEFAULT_CAPACITY 32
#define STACK_SIZE(stack) stack->count * stack->elemSize
#define STACK_END(stack) stack->data + STACK_SIZE(stack)

struct Stack
{
	bool expandible;
	size_t capacity;
	size_t count;
	size_t elemSize;
	void *data;
};

Stack *Stack_Create(size_t capacity, size_t elemSize)
{	
	Stack *stack = malloc(sizeof(struct Stack));
	if(stack == NULL)
		return NULL;
	
	if(capacity == 0)
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

bool Stack_Push(Stack *stack, void *elem)
{
	if(stack->count >= stack->capacity)
	{
		if(stack->expandible)
		{
			void *newDataBlock = (Stack*)malloc(STACK_SIZE(stack) * 2);
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

bool Stack_Pop(Stack *stack, void *elem)
{
	if(stack->count == 0)
		return false;

	if(elem != NULL)
		memcpy(elem, STACK_END(stack), stack->elemSize);
	stack->count--;
	return true;
}

bool Stack_Peek(const Stack *stack, void* elem)
{
	if(stack->count == 0)
		return false;

	memcpy(elem, STACK_END(stack), stack->elemSize);
	return true;
}

void Stack_Rotate(Stack *stack, int desp)
{
	if(stack->count <= 1)
		return;

	size_t division = (desp < 0) ? (-desp) % stack->count : stack->count - (desp % stack->count);
	if(division == 0)
		return;

	size_t min, smallSize, bigSize;
	min = (division < (stack->count - division)) ? division : (stack->count - division);
	smallSize = min * stack->elemSize;
	bigSize = (stack->count - min) * stack->elemSize;

	void *temp;
	if(stack->capacity >= (stack->count + min))
		temp = STACK_END(stack);
	else
	{
		temp = malloc(min * stack->elemSize);
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

	free(temp);
}

int Stack_Count(const Stack *stack)
{
	return stack->count;
}

void Stack_ToArray(const Stack *stack, void *array)
{
	if(stack->count == 0)
		return;
	memcpy(array, stack->data, STACK_SIZE(stack));
}

void Stack_Dispose(Stack *stack)
{
	free(stack->data);
	free(stack);
}
