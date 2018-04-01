#include <Collections/Stack.h>
#include <Collections/Queue.h>
#include <stdio.h>
#include <stdlib.h>
#include <alloca.h>

const int size = 7;
void printQueue(Queue queue)
{
	int count = Queue_Count(queue);
	printf("Count=%d: ", count);
	int *array = alloca(sizeof(int) * count);
	Queue_ToArray(queue, array);
	for(int i = 0; i < count; i++)
	{
		printf("%d ", array[i]);
	}
	printf("\n");
}

void printStack(Stack stack)
{
	int count = Stack_Count(stack);
	printf("Count=%d: ", count);
	int *array = alloca(sizeof(int) * count);
	Stack_ToArray(stack, array);
	for(int i = 0; i < count; i++)
	{
		printf("%d ", array[i]);
	}
	printf("\n");
}

int main()
{
	Stack stack = Stack_new(8, sizeof(int));
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
