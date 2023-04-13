#include "bintree.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

BinaryTree* bintree_initialize(int typeSize, char* typeName, int (*compFunction) (void*, void*), void (*printFunction) (void*))
{
	BinaryTree* tree = malloc(sizeof(*tree));

	if(tree == NULL)
		return NULL;
	tree->top = NULL;
	tree->itemSize = typeSize;

	tree->type = malloc(strlen(typeName)+1);
	strcpy(tree->type, typeName);

//	store the *compFunction function pointer in tree->comp
	tree->compare = compFunction;
//	store the *printFunction function pointer in tree->print	
	tree->print = printFunction;

	return tree;
}

BinaryTreeNode* bintree_create_node(int size, void* element)
{
	BinaryTreeNode* newNode = malloc(sizeof(*newNode));

	if(newNode == NULL)
		return NULL;

	newNode->data = malloc(size);
	memcpy(newNode->data, element, size);

	newNode->left = NULL;
	newNode->right = NULL;

	return newNode;
}

bool bintree_insert(BinaryTree* tree, void* element)
{
	if(tree == NULL || element == NULL)
		return false;

// 	check if the root node is NULL and store data into root node
//	if root node is not NULL check left and right node and fill respectively
	if(tree->top == NULL)
	{
		tree->top = bintree_create_node(tree->itemSize, element);

		if(tree->top == NULL)
			return false;
		return true;
	}
	else
	{
		return _bintree_insert_recursive(tree, tree->top, element);
	}

}

bool bintree_search(BinaryTree* tree, void* element)
{
	if(tree == NULL || element == NULL)
		return false;

	return _bintree_search_recursive(tree, tree->top, element);
}

void bintree_print_in_order(BinaryTree* tree)
{
	if(tree == NULL || tree->top == NULL)
		return;

	_bintree_in_order_recursive(tree, tree->top);
}

void bintree_print_pre_order(BinaryTree* tree)
{
	if(tree == NULL || tree->top == NULL)
		return;

	_bintree_pre_order_recursive(tree, tree->top);
}

void bintree_print_post_order(BinaryTree* tree)
{
	if(tree == NULL || tree->top == NULL)
		return;

	_bintree_post_order_recursive(tree, tree->top);
}

void bintree_print_reverse_order(BinaryTree* tree)
{
	if(tree == NULL || tree->top == NULL)
		return;

	_bintree_reverse_order_recursive(tree, tree->top);
}

bool _bintree_insert_recursive(BinaryTree* tree, BinaryTreeNode* node, void* element)
{
	if(tree->compare(node->data, element) < 0)
	{
		if(node->left == NULL)
		{
			node->left = bintree_create_node(tree->itemSize, element);
			if(node->left == NULL)
				return false;
		}
		else
		{
// 			check if the current node left node is NULL if not repeat until NULL
			return _bintree_insert_recursive(tree, node->left, element);
		}
	}

	else
	{
		if(node->right == NULL)
		{
			node->right = bintree_create_node(tree->itemSize, element);
			if(node->right == NULL)
				return false;

			return true;
		}
		else
		{
// 			check if the current node left node is NULL if not repeat until NULL
			return _bintree_insert_recursive(tree, node->right, element);
		}
	}
}

bool _bintree_search_recursive(BinaryTree* tree, BinaryTreeNode* node, void* element)
{
	int compare = tree->compare(node->data, element);

// 	if values are same return true
	if(compare == 0)
		return true;

// 	if element is less than node->data go left and keep checking until
// 	you find the value or the left node is NULL
	else if(compare < 0)
	{
		if(node->left == NULL)
			return false;
		else
			return _bintree_search_recursive(tree, node->left, element);
	}

// 	if element is less than node->data go right and keep checking until
// 	you find the value or the right node is NULL
	else if(compare > 0)
	{
		if(node->right == NULL)
			return false;
		else
			return _bintree_search_recursive(tree, node->right, element);
	}
}

void _bintree_in_order_recursive(BinaryTree* tree, BinaryTreeNode* node)
{
// 	check if left is NULL until the end of the tree
//	if it is not NULL keep checking until the left node is NULL
	if(node->left != NULL)
		_bintree_in_order_recursive(tree, node->left);

//	once the end of left is reached print the value
	tree->print(node->data);

	if(node->right != NULL)
		_bintree_in_order_recursive(tree, node->right);
}

void _bintree_pre_order_recursive(BinaryTree* tree, BinaryTreeNode* node)
{
	tree->print(node->data);

	if(node->left != NULL)
		_bintree_pre_order_recursive(tree, node->left);

	if(node->right != NULL)
		_bintree_pre_order_recursive(tree, node->right);
}

void _bintree_post_order_recursive(BinaryTree* tree, BinaryTreeNode* node)
{
	if(node->left != NULL)
		_bintree_post_order_recursive(tree, node->left);

	if(node->right != NULL)
		_bintree_post_order_recursive(tree, node->right);

	tree->print(node->data);
}

void _bintree_reverse_order_recursive(BinaryTree* tree, BinaryTreeNode* node)
{
	if(node->right != NULL)
		_bintree_reverse_order_recursive(tree, node->right);

	tree->print(node->data);

	if(node->left != NULL)
		_bintree_reverse_order_recursive(tree, node->left);
}
