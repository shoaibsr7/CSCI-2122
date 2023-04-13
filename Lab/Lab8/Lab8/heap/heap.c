#include "heap.h"
#include <stdlib.h>

Heap* heap_initialize(int dataTypeSize, char* dataTypeName, int (*compare)(void*, void*), void(*print)(void*))
{
	Heap* heap = malloc(sizeof (*heap));
	heap->list = alist_initialize(10, dataTypeSize, dataTypeName);
	heap->compare = compare;
	heap->print = print;

	return heap;
}

bool heap_insert(Heap* heap, void* element)
{
	alist_add(heap->list, element);

	int lastIndex = heap->list->size-1;

	return _heapify_up(heap, lastIndex);
}

void* heap_remove(Heap* heap)
{
	alist_swap(heap->list, 0, heap->list->size-1);

	void* remove_result = alist_remove(heap->list, heap->list->size-1);

	if(_heapify(heap, 0))
		return remove_result;
	else
		return NULL;
}

void* heap_peek(Heap* heap)
{
	return alist_get(heap->list, 0);
}

int heap_size(Heap* heap)
{
	return heap->list->size;
}

bool heap_contains(Heap* heap, void* element)
{
	if(alist_index_of(heap->list, element) >= 0)
		return true;
	else
		return false;
}

bool _heapify(Heap* heap, int index)
{

	if(heap == NULL)
		return false;

	// since its already heapified
	if(heap->list->size <= 1)
		return true;

	if(index < 0 || index >= heap->list->size)
		return false;

	// store the parent index in top
	int top = index;

	// store the left child in left
	int left = (2 * index) + 1;

	// similary for right
	int right = 2 * (index + 1);

	//store the value of parent in rootNode
	void* rootNode = alist_get(heap->list, top);

	// store the value of left child in leftNode
	void* leftNode = NULL;

	// check for index out of bound
	if(left < heap->list->size)
		// store value in leftNode
		leftNode = alist_get(heap->list, left);
	else 
		leftNode = NULL;

	// similaryly for rightNode
	void* rightNode = NULL;

	if (right < heap->list->size)
		rightNode = alist_get(heap->list, right);
	else
		rightNode = NULL;


	if(leftNode != NULL)
	{

		// comparing the value in parent node with children node

		// check for parent and left child
		if(heap->compare(rootNode, leftNode) < 0)
		{
			// switch the values in parent and left node
			rootNode = leftNode;
	
			// change the index for parent node value and left child value
			top = left;
		}
	}

	if(rightNode != NULL)
	{
		// similarly for right child
		if(heap->compare(rootNode, rightNode) < 0)
		{
			rootNode = rightNode;
			top = right;
		}
	}

	if(top != index)
	{
		alist_swap(heap->list, index, top);

		return _heapify(heap, top);
	}

	return true;
}

bool _heapify_up(Heap* heap, int index)
{
	if(index < 0 || index >= heap->list->size)
		return false;

	if(heap->list->size <= 1)
		return true;

	
	int parent = (index - 1) / 2;

	void* childValue = alist_get(heap->list, index);

	void* parentValue = alist_get(heap->list, parent);

	if(heap->compare(parentValue, childValue) < 0)
	{
		alist_swap(heap->list, parent, index);

		return _heapify_up(heap, parent);
	}

	return true;
}
