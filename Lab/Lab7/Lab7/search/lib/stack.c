#include "stack.h"
#include <stdlib.h>

Stack* stack_initialize(int typeSize, char* typeName)
{
	LinkedList* list = llist_initialize(typeSize, typeName);

	if(list == NULL)
		return NULL;

	Stack* stack = malloc(sizeof(*stack));

	if(stack == NULL)
	{
		llist_destroy(list);
		return NULL;
	}

	stack->stack = list;

	return stack;
}

bool stack_push(Stack* stack, void* element)
{
	if(stack == NULL)
		return false;

	return llist_add_first(stack->stack, element);
}

void* stack_pop(Stack* stack)
{
	if(stack == NULL)
		return NULL;

	return llist_remove_first(stack->stack);
}

void* stack_peek(Stack* stack)
{
	return llist_get(stack->stack, 0);
}

int stack_size(Stack* stack)
{
	if(stack == NULL)
		return -1;
	return stack->stack->size;
}

bool stack_contains(Stack* stack, void* element)
{
	if(stack == NULL)
		return false;

	int index = llist_index_of(stack->stack, element);

	if (index >= 0)
		return true;
	else
		return false;
}

bool stack_destroy(Stack* stack)
{
	if(stack == NULL)
		return false;

	llist_destroy(stack->stack);

	free(stack);

	return true;
}


