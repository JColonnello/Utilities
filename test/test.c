#include <Collections/Stack.h>
#include <Collections/Queue.h>
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

const int size = 7;
void printQueue(Queue *queue)
{
	int count = Queue_Count(queue);
	printf("Count=%d: ", count);
	int *array = malloc(sizeof(int) * count);
	Queue_ToArray(queue, array);
	for(int i = 0; i < count; i++)
	{
		printf("%d ", array[i]);
	}
	printf("\n");
	free(array);
}

void printStack(Stack *stack)
{
	int count = Stack_Count(stack);
	printf("Count=%d: ", count);
	int *array = malloc(sizeof(int) * count);
	Stack_ToArray(stack, array);
	for(int i = 0; i < count; i++)
	{
		printf("%d ", array[i]);
	}
	printf("\n");
	free(array);
}

int main()
{
	Stack *stack = Stack_Create(8, sizeof(int));
	printStack(stack);
	for(int i = 0; i < 8; i++)
	{
		Stack_Push(stack, &i);
		printStack(stack);
	}
	for(int i = 0; i < 8; i++)
	{
		Stack_Pop(stack, NULL);
		printStack(stack);
	}
	Stack_Dispose(stack);
	getchar();
}
