#include "Bag.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>

#define DEFAULT_CAPACITY 32

struct Bag
{
	size_t elemSize;
	size_t count;
	size_t maxCount;
	size_t size;
	void *data;
	char *flags;
};

static void reallocMem(Bag *bag, int newSize)
{
	//Reserve memory for data and flags
	size_t dataSize = bag->elemSize * newSize;
	size_t flagsSize = newSize / 8;
	size_t oldFlagsSize = bag->size / 8;
	uintptr_t *mem = realloc(bag->data, dataSize + flagsSize);
	//Copy flags to new array (data is copied on realloc)
	memcpy(mem + dataSize, bag->flags, oldFlagsSize);
	//Initialize new flags to 0
	size_t *ptr = mem + dataSize + oldFlagsSize;
	for(int block = oldFlagsSize; block < flagsSize; block++, ptr++)
		*ptr = 0;
	//Asign the new pointers and size
	bag->data = mem;
	bag->flags = (char*)(mem + dataSize);
	bag->size = newSize;
}

Bag *Bag_Create(size_t elemSize)
{
	//Reserve memory
	Bag *bag = malloc(sizeof(struct Bag));
	//Set variables
	bag->size = 0;
	bag->elemSize = elemSize;
	bag->count = 0;
	bag->maxCount = 0;
	
	//Reserve memory for data
	bag->data = NULL;
	bag->flags = NULL;
	reallocMem(bag, DEFAULT_CAPACITY);

	return bag;
}

int Bag_Add(Bag *bag, void *data)
{
	int pos = 0;
	//If we have reached the end of the array, expland the Bag
	if(bag->count == bag->size)
		reallocMem(bag, bag->size * 2);
	//If there are holes in the Bag check the flags
	if(bag->count < bag->maxCount)
	{
		//Access the flags by byte and then shift to
		//operate on the next bit
		for(int block = 0; block < bag->size / 8; block++)
		{
			int chunk = bag->flags[block];
			if(chunk == 255) continue;
			for(int bit = 0; bit < 8; bit++, pos++)
			{
				//If a hole is found set that flag to 1 and leave
				if(chunk <= 127) 
				{
					bag->flags[block] |= (uint8_t)128 >> bit;
					goto out;
				}
			}
		}
		out:
		bag->count++;
	}
	//Otherwise Add the element at the end
	else
	{
		int block = bag->count / 8;
		int offset = bag->count % 8;
		bag->flags[block] |= (uint8_t)128 >> offset;
		pos = bag->count++;
	}
	memcpy(bag->data + pos * bag->elemSize, data, bag->elemSize);
	if(bag->count > bag->maxCount) bag->maxCount = bag->count;
	return pos;
}

void Bag_Get(Bag *bag, int index, void *dest)
{
	memcpy(dest, bag->data + bag->elemSize * index, bag->elemSize);
}

void Bag_Remove(Bag *bag, int index)
{
	int block = index / 8;
	int offset = index % 8;

	//Set flag to 0
	bag->flags[block] &= ~((uint8_t)128 >> offset);
	bag->count--;
}

int Bag_Count(Bag *bag)
{
	return bag->count;
}

int Bag_ToIndexArray(Bag *bag, int *array)
{
	int arrayPos = 0;
	int bagPos = 0;
	//Search the flags
	for(int block = 0; block < bag->size / 8; block++)
	{
		uint8_t chunk = bag->flags[block];
		for(int bit = 0; bit < 8; bit++, bagPos++, chunk <<= 1)
		{
			//If the flag is 1 copy index to array
			if(chunk >= 128) 
			{
				array[arrayPos++] = bagPos;
			}
		}
	}
	return bag->count;
}

int Bag_ToArray(Bag *bag, void *array)
{
	size_t arrayPos = 0;
	size_t bagPos = 0;
	//Search the flags
	for(int block = 0; block < bag->size / 8; block++)
	{	
		uint8_t chunk = bag->flags[block];
		/*If all the flags in the chunk are 1 copy the
		* 8 elements to the array
		*/
		if(chunk == 255)
		{
			memcpy(array + bag->elemSize * arrayPos,
			 		bag->data + bag->elemSize * bagPos,
			 		 bag->elemSize * 8);
			arrayPos += 8;
			bagPos += 8;
		}
		//Otherwise check the flags == 1 and copy their elements
		else for(int bit = 0; bit < 8; bit++, bagPos++, chunk <<= 1)
		{
			if(chunk >= 128) 
			{
				memcpy(array + bag->elemSize * arrayPos,
			 		bag->data + bag->elemSize * bagPos,
			 		 bag->elemSize);
				arrayPos++;
			}
		}
	}
	return bag->count;
}

void Bag_Dispose(Bag *bag)
{
	free(bag->data);
	free(bag);
}

void *Bag_Data(Bag *bag)
{
	return bag->data;
}