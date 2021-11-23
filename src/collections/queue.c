#include <collections/queue.h>
#include <stdlib.h>
#include <string.h>

#define DEFAULT_CAPACITY 32

struct Queue
{
	bool expandible;
	size_t capacity;
	size_t count;
	size_t start;
	size_t end;
	size_t elemSize;
	void *data;
};

Queue *Queue_Create(size_t capacity, size_t elemSize)
{
	Queue *queue = malloc(sizeof(struct Queue));
	if (queue == NULL)
		return NULL;

	if (capacity == 0)
	{
		capacity = DEFAULT_CAPACITY;
		queue->expandible = true;
	}
	else
	{
		queue->expandible = false;
	}

	queue->data = malloc(capacity * elemSize);
	queue->capacity = capacity;
	queue->count = 0;
	queue->start = 0;
	queue->end = 0;
	queue->elemSize = elemSize;

	return queue;
}

void Queue_Enqueue(Queue *queue, void *elem)
{
	if (queue->count >= queue->capacity)
	{
		if (queue->expandible)
		{
			void *newDataBlock = (Queue *)malloc(queue->capacity * queue->elemSize * 2);
			if (newDataBlock != NULL)
			{
				Queue_ToArray(queue, newDataBlock);
				free(queue->data);
				queue->capacity *= 2;
				queue->data = newDataBlock;
				queue->start = 0;
				queue->end = queue->count;
				queue->count++;
			}
			else
				return;
		}
		else
		{
			queue->start++;
			queue->start %= queue->capacity;
		}
	}
	else
		queue->count++;

	memcpy(queue->data + queue->end * queue->elemSize, elem, queue->elemSize);
	queue->end++;
	queue->end %= queue->capacity;
}

bool Queue_Dequeue(Queue *queue, void *elem)
{
	if (queue->count == 0)
		return false;

	if (elem != NULL)
		memcpy(elem, queue->data + queue->start * queue->elemSize, queue->elemSize);
	queue->start++;
	queue->start %= queue->capacity;
	queue->count--;

	return true;
}

bool Queue_Peek(Queue *queue, void *elem)
{
	if (queue->count == 0)
		return false;

	memcpy(elem, queue->data + queue->start * queue->elemSize, queue->elemSize);
	return true;
}

int Queue_Count(Queue *queue)
{
	return queue->count;
}

void Queue_ToArray(Queue *queue, void *array)
{
	if (queue->count == 0)
		return;
	int size = (queue->end - queue->start) * queue->elemSize;
	if (size > 0)
	{
		memcpy(array, queue->data + queue->start * queue->elemSize, size);
	}
	else
	{
		size = (queue->capacity - queue->start) * queue->elemSize;
		memcpy(array, queue->data + queue->start * queue->elemSize, size);
		memcpy(array + size, queue->data, queue->end * queue->elemSize);
	}
}

void Queue_Dispose(Queue *queue)
{
	free(queue->data);
	free(queue);
}
