#include "Bag.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define DEFAULT_CAPACITY 32

struct Bag
{
	size_t elemSize;
	int count;
	int maxCount;
	size_t size;
	char *data;
	char *flags;
};

static void reallocMem(Bag Bag, int newSize)
{
	//Reserve memory for data and flags
	int dataSize = Bag->elemSize * newSize;
	int flagsSize = newSize / 8;
	int oldFlagsSize = Bag->size / 8;
	char *mem = realloc(Bag->data, dataSize + flagsSize);
	//Copy flags to new array (data is copied on realloc)
	memcpy(mem + dataSize, Bag->flags, oldFlagsSize);
	//Initialize new flags to 0
	uint8_t *ptr = mem + dataSize + oldFlagsSize;
	for(int block = oldFlagsSize; block < flagsSize; block++, ptr++) *ptr = 0;
	//Asign the new pointers and size
	Bag->data = mem;
	Bag->flags = mem + dataSize;
	Bag->size = newSize;
}

Bag Bag_new(int elemSize)
{
	//Reserve memory
	Bag Bag = malloc(sizeof(struct Bag));
	//Set variables
	Bag->size = 0;
	Bag->elemSize = elemSize;
	Bag->count = 0;
	Bag->maxCount = 0;
	
	//Reserve memory for data
	Bag->data = NULL;
	Bag->flags = NULL;
	reallocMem(Bag, DEFAULT_CAPACITY);

	return Bag;
}

int Bag_Add(Bag Bag, void *data)
{
	int pos = 0;
	//If we have reached the end of the array, expland the Bag
	if(Bag->count == Bag->size) reallocMem(Bag, Bag->size * 2);
	//If there are holes in the Bag check the flags
	if(Bag->count < Bag->maxCount)
	{
		//Access the flags by byte and then shift to
		//operate on the next bit
		for(int block = 0; block < Bag->size / 8; block++)
		{
			int chunk = Bag->flags[block];
			if(chunk == 255) continue;
			for(int bit = 0; bit < 8; bit++, pos++)
			{
				//If a hole is found set that flag to 1 and leave
				if(chunk <= 127) 
				{
					Bag->flags[block] |= (uint8_t)128 >> bit;
					goto out;
				}
			}
		}
		out:
		Bag->count++;
	}
	//Otherwise Add the element at the end
	else
	{
		int block = Bag->count / 8;
		int offset = Bag->count % 8;
		Bag->flags[block] |= (uint8_t)128 >> offset;
		pos = Bag->count++;
	}
	memcpy(&Bag->data[pos * Bag->elemSize], data, Bag->elemSize);
	if(Bag->count > Bag->maxCount) Bag->maxCount = Bag->count;
	return pos;
}

void Bag_Get(Bag Bag, int index, void *dest)
{
	memcpy(dest, &Bag->data[Bag->elemSize * index], Bag->elemSize);
}

void Bag_Remove(Bag Bag, int index)
{
	int block = index / 8;
	int offset = index % 8;

	//Set flag to 0
	Bag->flags[block] &= ~((uint8_t)128 >> offset);
	Bag->count--;
}

int Bag_Count(Bag Bag)
{
	return Bag->count;
}

int Bag_ToIndexArray(Bag Bag, void *array)
{
	int arrayPos = 0;
	int BagPos = 0;
	//Allocate the array
	int *arr = array;
	//Search the flags
	for(int block = 0; block < Bag->size / 8; block++)
	{
		uint8_t chunk = Bag->flags[block];
		for(int bit = 0; bit < 8; bit++, BagPos++, chunk <<= 1)
		{
			//If the flag is 1 copy index to array
			if(chunk >= 128) 
			{
				arr[arrayPos++] = BagPos;
			}
		}
	}
	return Bag->count;
}

int Bag_ToArray(Bag Bag, void *array)
{
	int arrayPos = 0;
	int BagPos = 0;
	//Allocate the array
	char *arr = array;
	//Search the flags
	for(int block = 0; block < Bag->size / 8; block++)
	{	
		uint8_t chunk = Bag->flags[block];
		/*If all the flags in the chunk are 1 copy the
		* 8 elements to the array
		*/
		if(chunk == 255)
		{
			memcpy(arr + Bag->elemSize * arrayPos,
			 		Bag->data + Bag->elemSize * BagPos,
			 		 Bag->elemSize * 8);
			arrayPos += 8;
			BagPos += 8;
		}
		//Otherwise check the flags == 1 and copy their elements
		else for(int bit = 0; bit < 8; bit++, BagPos++, chunk <<= 1)
		{
			if(chunk >= 128) 
			{
				memcpy(arr + Bag->elemSize * arrayPos,
			 		Bag->data + Bag->elemSize * BagPos,
			 		 Bag->elemSize);
				arrayPos++;
			}
		}
	}
	return Bag->count;
}

void Bag_Dispose(Bag Bag)
{
	free(Bag->data);
	free(Bag);
}

void *Bag_Data(Bag bag)
{
	return bag->data;
}