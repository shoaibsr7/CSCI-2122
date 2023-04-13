#ifndef __STACK_HEADER
#define __STACK_HEADER
#include "linked_list.h"
#include <stdbool.h>


typedef struct _Stack
{
	LinkedList* stack;
} Stack;

Stack* stack_initialize(int, char*);
bool   stack_push(Stack*, void*);
void*  stack_pop(Stack*);
void*  stack_peek(Stack*);
int    stack_size(Stack*);
bool   stack_contains(Stack*, void*);
bool   stack_destroy(Stack*);

#endif
