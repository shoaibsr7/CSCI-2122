#include "array_list.h"
#include <stdlib.h>
#include <string.h>

ArrayList* alist_initialize(int maxSize, int dataTypeSize, char* dataType)
{
	ArrayList* alist = malloc(sizeof(*alist));
	
	if (alist == NULL)
		return NULL;

	alist->arr = malloc(sizeof(*(alist->arr)) * maxSize);
	alist->size = 0;
	alist->maxSize = maxSize;
	alist->itemSize = dataTypeSize;
// strlen give the length of the string so for "Program" the output would be 7
// but while allocating memory you need an extra space to hold '\0' so the compiler knows
// that is the end of the string when it reads \0
	alist->type = malloc(strlen(dataType)+1);
	strcpy(alist->type, dataType);

	return alist;
}

// this method just adds element in the end.
bool alist_add(ArrayList* alist, void* element)
{
	if (alist == NULL)
		return false;

	return alist_add_at(alist, alist->size, element);
}

// this function adds the element at a specific index
bool alist_add_at(ArrayList* alist, int index, void* element)
{
	if(alist_add == NULL || element == NULL)
		return false;

	if(index<0 || index> alist->size)
		return false;
	if(alist->size == alist->maxSize)
	{
		bool success = _alist_resize(alist);

		if(!success)
			return false;
	}

	for(int i=alist->size; i > index; i--)
	{
		alist->arr[i] = alist->arr[i-1];
	}

	alist->arr[index] = malloc(alist->itemSize);

//	void *memcpy(void *dest, const void * src, size_t n)
//	dest − This is pointer to the destination array where the content is to be copied
//	src − This is pointer to the source of data to be copied
//	n − This is the number of bytes to be copied.
	memcpy(alist->arr[index], element, alist->itemSize);
	
	alist->size++;

	return true;
}

void alist_clear(ArrayList* alist)
{
	for (int i=0; i < alist->maxSize; i++)
	{
		free(alist->arr[i]);
		alist->arr[i] = NULL;
	}
	alist->size = 0;
}

void* alist_get(ArrayList* alist, int index)
{
	if(alist == NULL)
		return false;
	if(index < 0 || index >= alist->size)
		return NULL;
// allocate memory for the temp pointer by malloc (size of itemSize pointer) by creating a space in memory for temp of the size itemSize
	void* temp = memcpy(malloc(alist->itemSize), alist->arr[index], alist->itemSize);

	return temp;
}

int alist_index_of(ArrayList* alist, void* element)
{
	if(alist == NULL || element == NULL)
		return -1;

	for (int i=0; i < alist->size; i++)
	{

//	int memcmp(const void *str1, const void *str2, size_t n)
//	str1 − This is the pointer to a block of memory.
//	str2 − This is the pointer to a block of memory.		
//	n − This is the number of bytes to be compared.
		if(memcmp(alist->arr[i], element, alist->itemSize) == 0)
			return i;
	}

	return -1;
}

void* alist_remove(ArrayList* alist, int index)
{
	if(alist == NULL)
		return NULL;
	if(index < 0 || index >= alist->size)
		return NULL;

	void* element = alist->arr[index];

	for (int i = index; i < alist->size-1; i++)
	{
		alist->arr[i] = alist->arr[i+1];
	}
	alist->arr[alist->size-1] = NULL;

	alist->size--;

	return element;
}

bool alist_destroy(ArrayList* alist)
{
	alist_clear(alist);

	free(alist->type);

	free(alist);

	return true;
}

bool _alist_resize(ArrayList* alist)
{	
	if(alist == NULL)
		return false;
	
// void *realloc(void *ptr, size_t size)
// ptr − This is the pointer to a memory block previously allocated with malloc, calloc or realloc to be reallocated. 
// If this is NULL, a new block is allocated and a pointer to it is returned by the function.
// size − This is the new size for the memory block, in bytes. If it is 0 and ptr points to an existing block of memory, 
// the memory block pointed by ptr is deallocated and a NULL pointer is returned.
	void* tempPointer = realloc(alist->arr, alist->maxSize * 2 * sizeof(*(alist->arr)));

	if(tempPointer == NULL)
		return false;

	alist->maxSize *= 2;

	alist->arr = tempPointer;

	return true;
}
