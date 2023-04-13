#include "linked_list.h"
#include <stdlib.h>
#include <string.h>

LinkedList* llist_initialize(int typeSize, char* typeName)
{
	LinkedList* llist = malloc(sizeof(*llist));
	if(llist == NULL)
		return NULL;
	llist->first = NULL;
	llist->last = NULL;
	llist->size = 0;
	llist->itemSize = typeSize;
	llist->type = malloc(strlen(typeName)+1);
	strcpy(llist->type, typeName);

	return llist;
}

bool llist_add_first(LinkedList* llist, void* element)
{
	return llist_add_at(llist, 0, element);
}

bool llist_add_last(LinkedList* llist, void* element)
{
	return llist_add_at(llist, llist->size, element);
}

bool llist_add_at(LinkedList* llist, int index, void* element)
{
	if(llist == NULL || element == NULL)
		return false;
	if(index < 0 || index > llist->size)
		return false;

//	make a new node to store the data and later attach in the list
	Node *newNode = malloc(sizeof(*newNode));
//	assign space equal to the size of the item
	newNode->data = malloc(llist->itemSize);
//	copy the data given in the parameter into the newly created node
	memcpy(newNode->data, element, llist->itemSize);

//	empty list
	if(llist->size == 0)
	{
		llist->first = newNode;
		llist->last = newNode;
		newNode->prev = NULL;
		newNode->next = NULL;
	}

//	add at the starting
	else if(index == 0)
	{
		newNode->next = llist->first;
		newNode->prev = NULL;
		llist->first->prev = newNode;
		llist->first = newNode;
	}

// add at the end of the list	
	else if(index == llist->size)
	{
		newNode->prev = llist->last;
		newNode->next = NULL;
		llist->last->next = newNode;
		llist->last = newNode;
	}

//	at given index in between the list
	else
	{
		Node *temp = llist->first;

		for(int i=0; i<index; i++)
		{
			temp = temp->next;
		}
		newNode->prev = temp->prev;
		newNode->next = temp;
		temp->prev->next = newNode;
		temp->prev = newNode;
	}

	llist->size++;

	return true;
}

void* llist_get(LinkedList* llist, int index)
{
	if(llist == NULL)
		return NULL;
	if(index<0 || index >= llist->size)
		return NULL;

	Node *temp = llist->first;

	for(int i=0; i<index; i++)
	{
		temp = temp->next;
	}

	return temp->data;
}

int llist_index_of(LinkedList* llist, void* element)
{
	if(llist == NULL || element == NULL)
		return -1;

	Node *temp = llist->first;

	for(int i=0; i<llist->size; i++)
	{
		if(memcmp(temp->data, element, llist->itemSize) == 0)
		{
			return i;
		}
		temp = temp->next;
	}
	return -1;
}

void* llist_remove(LinkedList* llist, int index)
{
	if(llist == NULL)
		return NULL;

	if(index < 0 || index >= llist->size)
		return NULL;

	Node *temp = llist->first;

	for(int i=0; i < index; i++)
		temp = temp->next;

	if(llist->size == 1)
	{
		llist->first = NULL;
		llist->last = NULL;
	}

	else if(index == 0)
	{
		llist->first = temp->next;
		llist->first->prev == NULL;
	}

	else if(index == llist->size-1)
	{
		llist->last = temp->prev;
		llist->last->next = NULL;
	}

	else
	{
		temp->prev->next = temp->next;
		temp->next->prev = temp->prev;
	}

	llist->size--;

	void* data = temp->data;

	free (temp);

	return data;
}

void* llist_remove_first(LinkedList* llist)
{
	return llist_remove(llist, 0);
}

void* llist_remove_last(LinkedList* llist)
{
	if(llist == NULL)
		return false;

	return llist_remove(llist, llist->size-1);
}

bool llist_destroy(LinkedList* llist)
{
	if(llist == NULL)
		return false;

	if(llist->size > 0)
	{
		Node *current = llist->first;
		Node *next = NULL;

		for(int i = 0; i<llist->size; i++)
		{
			next = current->next;
			free(current->data);
			free(current);

			current = next;
		}
	}
	free(llist->type);
	free(llist);

	return true;
}

