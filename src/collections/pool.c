#include <collections/pool.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define DEFAULT_CAPACITY 32

struct Pool
{
	size_t elemSize;
	size_t count;
	size_t maxCount;
	size_t size;
	void *data;
	char *flags;
};

static bool inBounds(Pool *pool, int index)
{
	return (index < 0 || (size_t)index >= pool->count);
}

static void reallocMem(Pool *pool, int newSize)
{
	// Reserve memory for data and flags
	size_t dataSize = pool->elemSize * newSize;
	size_t flagsSize = newSize / 8;
	size_t oldFlagsSize = pool->size / 8;
	void *mem = realloc(pool->data, dataSize + flagsSize);
	// Copy flags to new array (data is copied on realloc)
	memmove(mem + dataSize, pool->flags, oldFlagsSize);
	// Initialize new flags to 0
	memset(mem + dataSize + oldFlagsSize, 0, flagsSize - oldFlagsSize);
	// Asign the new pointers and size
	pool->data = mem;
	pool->flags = (char *)(mem + dataSize);
	pool->size = newSize;
}

Pool *Pool_Create(size_t elemSize)
{
	// Reserve memory
	Pool *pool = malloc(sizeof(struct Pool));
	if (pool == NULL)
		return NULL;

	// Set variables
	pool->size = 0;
	pool->elemSize = elemSize;
	pool->count = 0;
	pool->maxCount = 0;

	// Reserve memory for data
	pool->data = NULL;
	pool->flags = NULL;
	reallocMem(pool, DEFAULT_CAPACITY);

	return pool;
}

int Pool_Add(Pool *pool, const void *data)
{
	int pos = 0;
	// If we have reached the end of the array, expand the Pool
	if (pool->count == pool->size)
		reallocMem(pool, pool->size * 2);
	// If there are holes in the Pool check the flags
	if (pool->count < pool->maxCount)
	{
		// Access the flags by byte and then shift to
		// operate on the next bit
		for (size_t block = 0; block < pool->size / 8; block++)
		{
			int chunk = pool->flags[block];
			if (chunk == 255)
				continue;
			for (int bit = 0; bit < 8; bit++, pos++)
			{
				// If a hole is found set that flag to 1 and leave
				if (chunk <= 127)
				{
					pool->flags[block] |= (uint8_t)128 >> bit;
					goto out;
				}
			}
		}
	out:
		pool->count++;
	}
	// Otherwise Add the element at the end
	else
	{
		int block = pool->count / 8;
		int offset = pool->count % 8;
		pool->flags[block] |= (uint8_t)128 >> offset;
		pos = pool->count++;
	}
	memcpy(pool->data + pos * pool->elemSize, data, pool->elemSize);
	if (pool->count > pool->maxCount)
		pool->maxCount = pool->count;
	return pos;
}

void Pool_Get(Pool *pool, int index, void *dest)
{
	if (!inBounds(pool, index))
		return;
	memcpy(dest, pool->data + pool->elemSize * index, pool->elemSize);
}

void *Pool_GetRef(Pool *pool, int index)
{
	if (!inBounds(pool, index))
		return NULL;
	return pool->data + pool->elemSize * index;
}

void Pool_Remove(Pool *pool, int index)
{
	if (!inBounds(pool, index))
		return;

	int block = index / 8;
	int offset = index % 8;

	// Set flag to 0
	pool->flags[block] &= ~((uint8_t)128 >> offset);
	pool->count--;
}

int Pool_Count(Pool *pool)
{
	return pool->count;
}

int Pool_ToIndexArray(Pool *pool, int *array)
{
	int arrayPos = 0;
	int poolPos = 0;
	// Search the flags
	for (size_t block = 0; block < pool->size / 8; block++)
	{
		uint8_t chunk = pool->flags[block];
		for (int bit = 0; bit < 8; bit++, poolPos++, chunk <<= 1)
		{
			// If the flag is 1 copy index to array
			if (chunk >= 128)
			{
				array[arrayPos++] = poolPos;
			}
		}
	}
	return pool->count;
}

int Pool_ToArray(Pool *pool, void *array)
{
	size_t arrayPos = 0;
	size_t poolPos = 0;
	// Search the flags
	for (size_t block = 0; block < pool->size / 8; block++)
	{
		uint8_t chunk = pool->flags[block];
		/*If all the flags in the chunk are 1 copy the
		 * 8 elements to the array
		 */
		if (chunk == 255)
		{
			memcpy(array + pool->elemSize * arrayPos, pool->data + pool->elemSize * poolPos, pool->elemSize * 8);
			arrayPos += 8;
			poolPos += 8;
		}
		// Otherwise check the flags == 1 and copy their elements
		else
			for (int bit = 0; bit < 8; bit++, poolPos++, chunk <<= 1)
			{
				if (chunk >= 128)
				{
					memcpy(array + pool->elemSize * arrayPos, pool->data + pool->elemSize * poolPos, pool->elemSize);
					arrayPos++;
				}
			}
	}
	return pool->count;
}

void Pool_Dispose(Pool *pool)
{
	free(pool->data);
	free(pool);
}

void *Pool_Data(Pool *pool)
{
	return pool->data;
}
