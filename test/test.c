#include <collections/stack.h>
#include <collections/queue.h>
#include <collections/list.h>
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
/*
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
*/

int comp(const int *a, const int *b)
{
	return *a == *b;
}

int main()
{
	List *list = List_Create(sizeof(int));
	/*
	for (int i = 0; i < 5; ++i)
	{
		List_Add(list, &i);
	}
	for (int i = 5; i >= 0; --i)
	{
		List_Add(list, &i);
	}
	*/
	int r = 3;
	List_Add(list, &r);
	r = 2;
	List_Add(list, &r);
	int *array, count;
	List_RemoveLast(list, &r, (int(*)(const void*,const void*))comp);
	r = 3;
	List_RemoveLast(list, &r, (int(*)(const void*,const void*))comp);
	count = List_ToArray(list, (void**)&array);
	for (int i = 0; i < count; ++i)
	{
		printf("%d ", array[i]);
	}
	List_Dispose(list);
	free(array);
	printf("\n");
}