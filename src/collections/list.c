#include "list.h"
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct Node Node;
struct Node
{
	Node *next;
	char data[];
};

struct List
{
	size_t size;
	size_t count;
	Node *first;
	Node *last;
};

List *List_Create(size_t size)
{
	List *list = calloc(sizeof(struct List), 1);
	list->size = size;

	return list;
}

void List_Dispose(List *list)
{
	Node *last, *node = list->first;
	while(node)
	{
		last = node;
		node = node->next;
		free(last);
	}
	free(list);
}

static Node *createNode(const void *data, size_t size)
{
	Node *node = malloc(sizeof(struct Node) + size);
	if(!node)
		return NULL;
	memcpy(node->data, data, size);
	node->next = NULL;
	return node;
}

static bool removeLastNode(List *list, Node **node, const void *e, int (*equals)(const void *a, const void *b))
{
	if(*node == NULL)
		return 0;
	Node *next = (*node)->next;
	if(removeLastNode(list, &(*node)->next, e, equals))
	{
		if(next == list->last)
			list->last = *node;
		return 1;
	}
	if(equals((*node)->data, e))
	{
		Node *tmp = (*node);
		*node = (*node)->next;
		free(tmp);
		list->count--;
		return 1;
	}
	else
		return 0;
}

bool List_RemoveLast(List *list, const void *e, int (*equals)(const void *a, const void *b))
{
	bool r = removeLastNode(list, &list->first, e, equals);
	if(r && list->count == 0)
		list->last = NULL;
	return r;
}

void List_Add(List *list, const void *e)
{
	Node *node = createNode(e, list->size);
	memcpy(node->data, e, list->size);
	if(list->count == 0)
	{
		list->first = node;
		list->last = node;
	}
	else
	{
		list->last->next = node;
		list->last = node;
	}
	list->count++;
}

void List_Insert(List *list, size_t idx, const void *e);
bool List_Get(const List *list, size_t idx, void *dest);
bool List_RemoveIndex(List *list, size_t idx);
bool List_Remove(List *list, const void *e);
size_t List_Count(const List *list);
bool List_IsEmpty(const List *list);
bool List_Contains(const List *list, const void *e);
void List_Clear(List *list);

int List_ToArray(const List *list, void **array)
{
	size_t length = list->size * list->count;
	*array = malloc(length);
	if(*array)
	{
		Node *node = list->first;
		char *ptr = *array;
		for(int i = 0; node; i++, node = node->next)
		{
			memcpy(ptr + list->size * i, node->data, list->size);
		}
	}
	return list->count;
}