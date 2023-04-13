#include "dictionary.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Dictionary* dict_initialize(int (*comp)(void*, void*), void (*print)(void*))
{
	Dictionary* dict = malloc(sizeof(Dictionary));

	dict->tree = bintree_initialize(sizeof(Pair), "Pair", comp, print);

	return dict;
}

bool dict_insert(Dictionary* dict, void* key,void* value)
{
	Pair* pair = malloc(sizeof(Pair));
	
	pair->first = key;

	pair->second = value;

	return bintree_insert_replace(dict->tree, pair);
}

void* dict_get(Dictionary* dict, void* key)
{
	Pair* temp = malloc(sizeof(Pair));
	
	temp->first = key;
	temp->second = NULL;

	BinaryTreeNode* node = dict->tree->top;

	while(node != NULL)
	{
		if(dict->tree->compare(node->data, temp) == 0)
			return ((Pair*)node->data)->second;
			
		else if (dict->tree->compare(node->data, temp) < 0)
			node = node->left;

		else
			node = node->right;
	}

	return NULL;
}

ArrayList* dict_key_list(Dictionary* dict, int keySize)
{
	ArrayList* alist = alist_initialize(100, keySize, "key");

	BinaryTreeNode* node = dict->tree->top;

	_dict_key_list_recursive(node, alist);

	return alist;
}

ArrayList* _dict_key_list_recursive(BinaryTreeNode* node, ArrayList* alist)
{
	if(node->left != NULL)
		_dict_key_list_recursive(node->left, alist);

	alist_add(alist, ((Pair*)node->data)->first);

	if(node->right != NULL)
		_dict_key_list_recursive(node->right, alist);
}

bool dict_contains(Dictionary* dict, void* key)
{
	Pair* pair = malloc(sizeof(Pair));
	pair->first = key;
	pair->second = NULL;

	return bintree_search(dict->tree, pair);
}