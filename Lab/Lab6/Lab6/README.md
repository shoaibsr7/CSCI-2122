# Introduction

This lab is designed to introduce you to queues, stacks, and binary
trees. By the end of this lab, you will be expected to understand those
concepts. In the next lab we will be expanding your trees to encompass
heaps (priority queues) and we will be using queues and stacks to
perform depth-first and breadth-first searches, so it’s important that
you do your best to understand the concepts laid out below.

In this lab you are expected to perform the basics of cloning your Lab 6
repository from the GitLab course group. A link to the course group can
be found
[<span style="color: blue">here</span>](https://git.cs.dal.ca/courses/2022-fall/csci-2122)
and your repository can be found in the Lab6 subgroup. See the Lab
Technical Document for more information on using git. You will notice
that your repository has a file in the `Lab6` directory named
`delete_this_file`. Due to the limitations of GitLab, we are not
able to push completely empty directories. Before you push your work to
your repository (which should be in the `Lab6` directory anyway), make
sure to first use the <kbd>git rm</kbd> command to remove the extra file. If
you do not, your pipeline could fail.  

**Be sure to read this entire document before starting!**

# Table of Contents
[[_TOC_]]



# Queues

A queue is a common data structure which performs operations in a “first
in, first out" order. This is often abbreviated as FIFO. A common
analogy is to imagine that you are in line at the bank. The first person
in line will be the first person served at one of the tellers. In this
case, it’s a first come, first served situation where the first "thing"
added to the queue is also the first thing we work with when the time
comes to do some processing.

In this lab, your task will be to implement a queue using any designs or
libraries of your own make, including ones you have written before in
this class. The goal is that your queue should be able to hold any
reasonable number of items such that we are able to minimally perform
the three basic queue operations: **enqueue**, **dequeue**, and
**peek**. In addition to the three basic queue operations, you’ll also
be expected to provide **size** and **contains** function.

Your queue will have an initialization function, which should return a
pointer to a typedefed struct called Queue (see the Queue contract for
more information). It should start as an array or list (your choice) and
should have no elements in it to start. Similar to previous labs, your
queue will hold typeless data in the form of void pointers so that you
don’t have to worry about creating hard-typed queues.

## enqueue

Whenever a user wants to add an item to a queue, they will need to call
the **enqueue** function. The enqueue function should accept a pointer
to a Queue and a pointer to an element, then add that element to one end
of its list. This can be at the start of the list or the end of the
list, as long as you are consistent every time. Every time an element is
added, the size of your queue should increase.

## dequeue

Whenever a user wants to retrieve an item from a queue, they will need
to call the **dequeue** function. The dequeue function should accept a
pointer to a Queue, then remove and return the item which has been in
the queue the longest in the form of a void pointer. Every time an
element is removed, the size of your queue should decrease. The item
removed should be from the opposite end of the list compared to where
you add (enqueue) them.

## peek

A user is allowed to look at whatever the current oldest item is in your
queue using the **peek** function. The peek function should accept a
pointer to a Queue, then return a void pointer representing the item at
the front of the queue, which should be the oldest item. Since the item
is not removed, the size of the queue should not change.

## size

The size function should return the number of items remaining in a
Queue. It will accept a pointer to a Queue and return an integer
representing the number of items currently in that queue.

## contains

The contains function will accept a pointer to a Queue and a void
pointer to an element, then return true if the element is currently in
the queue. If the element is not in the queue, this should return false
instead.

# Stacks

Stacks are similar to queues in that they are also arrays/lists which
contain some number of items, but instead of being “first in, first out"
(FIFO), they are set up to be “last in, first out" (LIFO). You are
likely to hear about stacks often throughout your university career in
Computer Science, so now is a great time to get accustomed to how they
work! These instructions are largely similar to queues and will
function the same, except in a few areas. We will only talk about the
differences below: assume anything we don’t mention is the same as the
queues implementation.

In this lab, your task will be to implement a stack using any designs or
libraries of your own make, including ones you have written before in
this class. The goal is that your stack should be able to hold any
reasonable number of items such that we are able to minimally perform
the three basic stack operations: **push**, **pop**, and **peek**. In
addition to the three basic stack operations, you’ll also be expected to
provide **size** and **contains** function.

Your stack will have an initialization function, which should return a
pointer to a typedefed struct called Stack (see the Stack contract for
more information). It should start as an array or list (your choice) and
should have no elements in it to start. Similar to previous labs, your
stack will hold typeless data in the form of void pointers so that you
don’t have to worry about creating hard-typed queues.

## push

This function is similar to enqueue, except that we generally refer to
items as being pushed to the top of the stack. This can be either end of
the list, similar to the queue, as long as you’re consistent.

## pop

This function is similar to dequeue, except that it retrieves an item
from the same end of the list at which the elements are added. This
means that whatever item was most recently pushed to the stack is the
next item which will be popped, not the oldest.

## peek

The peek function is similar to the queue’s peek function, except it
returns a pointer to the last element pushed to the stack, not the
oldest.

# Binary Trees

Binary trees are a data structure which allows you to create a hierarchy
of data by setting some condition on how the data is stored. In computer
science, binary trees are a very important data type as they allow you
to store and search for data quickly by following a relatively short
series of steps in order to determine if the data you’re looking for is
present in your collection.

A binary tree can be represented in a number of ways, but in this lab
we’re going to use a struct to define the important components of a
binary tree. In later labs we will be expanding on our binary trees to
solve more complex problems (such as priority queues and tree-search
methods), but for now we will work with a very basic binary tree and do
some simple searches and traversals so we have an opportunity to learn
exactly how they function.

A binary tree is made up a series of **nodes** (called tree nodes or
vertices) and edges. An **edge** is a path which leads from one node to
another node as they’re joined together. Each node in a binary is
allowed to have two such edges leaving it, thus giving it the binary
name. These edges point to other nodes, and the nodes they connect to
are known as the **children** of the node. A node which is pointing to
such a child node is referred to as a **parent node**. Every binary tree
starts with a single node at the top, referred to as a **root node**,
and traditionally builds downward, although there’s no reason why you
can’t flip it upside down and say it grows upward instead. A tree is
technically a specific type of graph, and you will learn more about
graphs in your third year courses, such as *Design and Analysis of
Algorithms I*.

Since the tree only grows in one direction, we can make a few simple
observations. First, a binary tree is **directed**, meaning that the
edges leaving a node point at other nodes, but those edges are not
bi-directional. Thus, when a node is added, it does not necessarily know
who its parent is. There is also a condition such that a binary tree is
not allowed to have a **cycle** in it. A cycle is a series of
edges/nodes such that if you start at some node $`V`$ and follow some
series of edges, you will arrive back at $`V`$. A binary tree is not
allowed to do this, and thus you never have to worry about your nodes
circling back around to places you’ve already been when you’re
searching.  

![image](CI/docs/Binary_Tree.png)

In the above image, you can see the basic anatomy of an integer-based
binary tree. The node at the top (21) is the root note, as it has no
parent nodes. As integers are inserted into the binary tree, they follow
a specific pattern for determining where they should be placed in the
tree. When an integer is added, we compare it to the value of the root
node. If it is less than the root node’s stored value, then we should
add it on the left side of our tree. If it is equal to, or greater than,
the root node’s value, we should add it to the right side of our tree.
For example, if we wanted to add 13 to this tree, we would see 13 is
less than 21, and thus we would want to add it on the left side, which
is referred to as the **left subtree**. We then compare 13 to 9, and
seeing that it’s greater, we want to add it to 9’s **right subtree**,
and then to the left subtree of 16.

In our diagram, we are designating edges to other nodes (pointers) in
blue, and edges without nodes (which we can imagine are null pointers).
If we ever get to a point where we’re trying to add something to a
subtree which is null, we create a new node that holds the value we want
to insert and update that edge to refer to the new node. In our above
example, 13 would be placed inside a node with two null edges and the
left edge of 16’s node would point to the new 13 node.

If you use some simple logic, you should notice that the integer binary
tree actually sorts the values into ranges. For example, the fact that
the 16 is to the *left* of 21, and to the *right* of 9 suggests that it
must winter in \[9, 21\], which is obviously true. This extends to all
values in the binary tree. For example, if a node is to the right of 24
and the left of 33, so it must at least be in the range \[24, 33\]. In
our example binary tree, we can see that the node is 27, and thus the
observation holds. This is an example of the sorting power of a binary
tree.

While it’s possible to represent binary trees with just an array, we
will be using a struct with pointers to enable us to practice recursive
algorithms. It turns out that from the point of view of a function
working on a single node, any position in the tree can be traversed to
similar to the way you iterate through a linked list: by continuously
updating a function with the next node so you can perform the same
action repeatedly until you arrive at the location you desire. This is
done via recursion and is a powerful tool for operating on tree
structures.

## Initializing a Binary Tree

In this lab, binary trees come with two structures: the tree itself and
the individual nodes. A tree node consists of three fields: the data (a
void pointer), and a left and right pointer to another tree node. By
default, the left and right pointers of any node are set to null. As a
tree grows, these are updated to reflect new nodes being added to the
left and right subtrees of each node. A tree consists of the things
you’ve seen before, such as the name of the data type it holds and the
size of that data type. Similar to a linked list, it also holds a
starting node so you always have access to your root node.

In addition to those fields a binary tree will also contain two other
variables: a function pointer to a **compare** function, and a function
pointer to a **print** function. These will be provided by the user
during initialization and will be used in your code to ensure your
binary tree is built properly.

## Inserting Values into a Binary Tree

In this lab, we will focus very simply on creating a binary tree of
integers. As such, inserting values should be relatively simple. First,
if your binary tree does not yet have a root node, if you insert a value
it can become your first node. As mentioned above, this means creating a
node, adding the data value to it, setting its child (left and right)
pointers to null, then setting it as the root node in the tree struct.

If there is already a root node, you will need to write a simple
recursive function to find the correct place to insert your value. Start
at the root node and compare your inserted value to the root node’s
value. If the inserted value is less than the root node’s value, your
node should be placed in the left subtree. Otherwise it should be placed
in the right subtree.

Once you have determined which subtree to place it in, you must first
make a check to see if the subtree is null. If so, make a node with the
inserted value and have the root node’s correct child pointer point to
it. If the subtree is not null, you can recursively call your insertion
function on the node in the designated subtree. Once a node has been
inserted, you can end your function with an appropriate return.

## Searching a Binary Tree

To search a binary tree, we follow the same style of function as
outlined above for inserting, with a few minor changes. First, rather
than creating nodes, we are checking to see if a given searched value
matches any nodes along the way. If we ever reach a node where the data
in the node matches the data we’re searching for, we return true.
However, if we are searching and end up attempting to follow a subtree
which *should* contain the value, but that subtree is null, then the
value must not exist in our tree, thus we should return false.

## Printing the Values of a Binary Tree

One great feature of an integer-based binary tree is that it will
naturally sort all of your data, and do so very quickly. If you were to
imagine reading the values from left-to-right based on their absolute
ordering, you would end up with the numbers printed in
smallest-to-largest order. This particular order is referred to as an
**in-order** traversal of the binary tree, where a traversal is a way of
moving from node-to-node in a tree following a specific pattern.

In order to achieve such a result, you can recursively perform a
combination of value printing and pointer-following in order to reach
(and print) every node in the binary tree in a particular pattern. To
print an in-order node pattern, you would start at the root node.
Recursively print the left subtree of the root node, then print the
value of the root node, then print the right subtree of the root node.
If your recursive function is set up properly, you will traverse and
print the tree in the following way:

![image](CI/docs/Binary_Tree_InOrder.png)

Since the algorithm we have defined only prints each node’s value after
the left subtree has been printed, we will get the values printed in
left-to-right order. For this binary tree, that output would be
`{3, 9, 16, 21, 24, 27, 33, 42}`.

There are several types of basic traversals which can be performed on a
binary tree, as follows (including the one we just discussed):

1.  **In-Order**: Prints the state of the tree from left-to-right. Can be performed by recursively printing the left subtree of a node, printing the node’s value, then recursively printing the right subtree of a node.
2.  **Pre-Order**: Prints the state of the tree such that you print the value of the node, followed by recursively printing the left subtree, then the right subtree.
3.  **Post-Order**: Prints the state of the tree such that you recursively print the left subtree, followed by resurively printing the right subtree, followed by printing the value of the node.
4.  **Reverse-Order**: Prints the state of the tree from right-to-left. Performs the in-order operations in reverse.

## The Compare and Print Functions

You may remember that your binary tree stores two function pointers.
Because your binary tree relies on the typing of your tree in order to
make comparisons and to print values in traversals, the user
initializing the binary tree is required to pass in a function for
comparing two values in the tree, as well as a function which can print
a binary tree node value.

The **compare** function accepts two void pointers and returns an int.
It should cast the two pointers to relevant values, then compare them.
It should output the following values based on the state of the values:

1.  If the two values are considered equal, return 0.
2.  If the second value is larger than the first value (or should appear later), return a value greater than 0.
3.  If the second value is smaller than the first value (or should appear sooner), return a value less than 0.

The **print** function should accept a single void pointer and return
nothing. Convert the pointer to an appropriate value based on the binary
tree’s type and print that value to the screen, followed by a single
space.

Here, you can see the compare and print functions provided to your
binary tree’s initialize function:

``` c
int compareInt(void* a, void* b)
{
    return *((int*)b) - *((int*)a);
}

void printInt(void* a)
{
    printf("%d ", *((int*)a));
}
```

## Recursion on Binary Trees

We have explained recursion in previous labs, but can provide some extra
tips here for how to handle recursion with binary trees.

1.  Remember that every node in your binary tree is the same as all of the others. This means it should be easy to treat each node independently and make recursive calls on the children of the current node to continue moving through the tree. If a function asks for a BinaryTreeNode as a pointer, odds are good we expect you to call that function on a child node at each recursive step!
2.  It is more efficient to test for NULL children in the current node and not recurse on a NULL pointer. This saves a recursive step and should make your code easier to follow. Whenever possible, only make a recursive call to a node that you know exists.
3.  Remember to use the compare function stored in your tree to decide which child node to check. Creating a compare function for integers is very simple, as you’re simply returning the difference between integer 2 and integer 1.
4.  Remember to use a return statement in front of your recursive calls when you expect them to be returning a value. It makes your programs faster if you can make a guarantee to C that the return statement the last thing a function does.

# Lab 6 Function Contracts

In this lab you will be responsible for fulfilling three lab contracts:
the **Queue** contract, the **Stack** contract, and the **Binary Tree**
contract. Each contract is designed to test you on some of the things
you’ve learned throughout the instruction portion of this lab.

All contracts must be completed exactly as the requirements are laid
out. Be very careful to thoroughly read the contract instructions before
proceeding. This does not, however, preclude you from writing **more**
functions than you are asked for. You may write as many additional
functions as you wish in your C source files.

All contracts are designed to be submitted without a main function, but
that does not mean you cannot write a main function in order to test
your code yourself. It may be more convenient for you to write a C
source file with a main function by itself and take advantage of the
compiler’s ability to link files together by accepting multiple source
files as inputs. When you push your code to Gitlab, you don’t need to
<kbd>git add</kbd> any of your extra main function source files.

The programs you write for this lab will not be compiled with any
additional libraries by us, although your repository and Makefiles can
include/compile any additional libraries or files you need.

For those of you who are concerned, when deciding which naming
conventions you want to use in your code, favour consistency in style,
not dedication to a style that doesn’t work.  

## Queue

### Problem

You must create a structure and set of functions for managing a queue.

### Preconditions

You are required to write a program for handling queues. This consists
of `queue.c`, which should contain all of your function
implementations, and , which should contain your structure definition,
any necessary typedefs, and all of your forward function declarations.
When you compile, you will need to include the source file in your
command in order to ensure the functions exist during the linking
process. You may include any additional helper functions as you see fit.
Since you are dealing with pointers, you will need to check all of your
pointers to ensure they are not null. Trying to perform operations on
null will lead to segmentation faults or other program crashes at
run-time.

Your Queue is a typedeffed structure, but as long as the type works with
all of the function contracts listed below, you’re free to design your
struct however you’d like.

The details of the queue functionality are described in the **Queue**
section of this document. The **bool** type referenced in this contract
is found in `<stdbool.h>`. You are expected to do basic error
checking (such as checking for null pointers and correct index
boundaries).

Your **queue** program must include the following struct (typedef-ed
appropriately):

| **Structure Name**      | **Fields**      | **Functionality**            |
| :---------------------- | :-------------- | :--------------------------- |
| \_Queue (typedef Queue) | Any you’d like. | Whatever you deem necessary. |

Your **queue** program must include the following functions:

| **Requirement**  | **Conditions**                                                                                |
| :--------------- | :-------------------------------------------------------------------------------------------- |
| Function         | Queue\* queue\_initialize(int, char\*)                                                        |
| Input Parameters | An integer for setting the data type size and a string representing the name of the data type being stored.                                                                            |
| Return Value     | A pointer to an initialized Queue.                                                            |
| Notes            | None.                                                                                         |

| **Requirement**  | **Conditions**                                                                                |
| :--------------- | :-------------------------------------------------------------------------------------------- |
| Function         | bool queue\_enqueue(Queue\*, void\*)                                                          |
| Input Parameters | A pointer to a Queue, and a void pointer to an element.                                       |
| Return Value     | True if the element was successfully added to the queue. Otherwise false.                     |
| Notes            | This function should insert the given element at the end of the queue.                        |

| **Requirement**  | **Conditions**                                                                                |
| :--------------- | :-------------------------------------------------------------------------------------------- |
| Function         | void\* queue\_dequeue(Queue\*)                                                                |
| Input Parameters | A pointer to a Queue.                                                                         |
| Return Value     | A void pointer to the element that was removed.                                               |
| Notes            | This function should remove the element at the front of the queue and return a pointer to it. |

| **Requirement**  | **Conditions**                                                                                |
| :--------------- | :-------------------------------------------------------------------------------------------- |
| Function         | void\* queue\_peek(Queue\*)                                                                   |
| Input Parameters | A pointer to a Queue.                                                                         |
| Return Value     | A void pointer to the element at the front of the queue.                                      |
| Notes            | This function should return a pointer to the element at the front of the queue.               |

| **Requirement**  | **Conditions**                                                                                |
| :--------------- | :-------------------------------------------------------------------------------------------- |
| Function         | int queue\_size(Queue\*)                                                                      |
| Input Parameters | A pointer to a Queue.                                                                         |
| Return Value     | An integer representing the number of elements in the queue.                                  |
| Notes            | None.                                                                                         |

| **Requirement**  | **Conditions**                                                                                |
| :--------------- | :-------------------------------------------------------------------------------------------- |
| Function         | bool queue\_contains(Queue\*, void\*)                                                         |
| Input Parameters | A pointer to a Queue and a void pointer to an element.                                        |
| Return Value     | True if the given item is in the queue. Otherwise false.                                      |
| Notes            | None.                                                                                         |

| **Requirement**  | **Conditions**                                                                                |
| :--------------- | :-------------------------------------------------------------------------------------------- |
| Function         | bool queue\_destroy(Queue\*)                                                                  |
| Input Parameters | A pointer to a Queue.                                                                         |
| Return Value     | True if the queue is successfully deallocated. Otherwise false.                               |
| Notes            | This function should deallocate any remaining elements and then the queue itself.             |

### Postconditions

Your program should be capable of producing and destroying Queue (_queue) structures. All of the functions should be capable of
executing without crashing. Failure states should be handled by return
values. If a function with a void return type fails, it does not need to
be reported.  

### Restrictions

None.

### File Requirements

This contract requires you to provide a C source file named `queue.c`
and a C header file named `queue.h`. Your header files should contain
your forward declarations, struct definitions and typedefs, as well as
any library imports (includes) you may need. Always protect your header
with a define guard. Your source files must not contain any main
functions when you submit, or your program will fail during testing.

In addition to the C files, you will also be required to make a Makefile
for the **queue** program. Your program will be compiled by executing
**make**. Your Makefile should produce both an `queue.o` file and an
**queue** executable file by compiling your code with the `queueM.o`
file located in `CI/objects/queue`.

Your source, header, and make files should be placed in the
`Lab6/queue/` directory in your GitLab repository.

### Testing

To test your code, you can compile your source files with the
`queueM.o` object file found in `CI/objects/queue`. Your program can
then be executed as normal. The object file contains a main function, so
you do not need to provide your own. Using a Makefile for compiling
these files together can save you a lot of time.

### Sample Inputs and Outputs

We provide a complete output file, but do not use it for comparison in
the pipeline. The main object file for this program will test your
various functions on a Queue. Your code should minimally be able to
complete the test main function in the object file, but you may find it
more convenient to test your functions with your own main function
first. **Writing your own main function for testing purposes can be
extremely helpful.**

## Stack

### Problem

You must create a structure and set of functions for managing a stack.

### Preconditions

You are required to write a program for handling stacks. This consists
of `stack.c`, which should contain all of your function
implementations, and , which should contain your structure definition,
any necessary typedefs, and all of your forward function declarations.
When you compile, you will need to include the source file in your
command in order to ensure the functions exist during the linking
process. You may include any additional helper functions as you see fit.
Since you are dealing with pointers, you will need to check all of your
pointers to ensure they are not null. Trying to perform operations on
null will lead to segmentation faults or other program crashes at
run-time.

Your stack will hold a specific data type (and that data type only) as
defined by the initialization parameters. The size of the data type held
is provided, as is the name.

The details of the stack functionality are described in the **Stacks**
section of this document. The **bool** type referenced in this contract
is found in `<stdbool.h>`. You are expected to do basic error
checking (such as checking for null pointers and correct index
boundaries).

Your **stack** program must include the following struct (typedef-ed
appropriately):

| **Structure Name**      | **Fields**      | **Functionality**            |
| :---------------------- | :-------------- | :--------------------------- |
| \_Stack (typedef Stack) | Any you’d like. | Whatever you deem necessary. |

Your **stack** program must include the following functions:

| **Requirement**  | **Conditions**                                                                            |
| :--------------- | :---------------------------------------------------------------------------------------- |
| Function         | Stack\* stack\_initialize(int, char\*)                                                    |
| Input Parameters | An integer for setting the data type size and a string representing the name of the data. |
| Return Value     | A pointer to an initialized Stack.                                                        |
| Notes            | None.                                                                                     |

| **Requirement**  | **Conditions**                                                                            |
| :--------------- | :---------------------------------------------------------------------------------------- |
| Function         | bool stack\_push(Stack\*, void\*)                                                         |
| Input Parameters | A pointer to a Stack, and a void pointer to an element.                                   |
| Return Value     | True if the element was successfully pushed to the stack. Otherwise false.                |
| Notes            | This function should push the given element to the top of the stack.                      |

| **Requirement**  | **Conditions**                                                                            |
| :--------------- | :---------------------------------------------------------------------------------------- |
| Function         | void\* stack\_pop(Stack\*)                                                                |
| Input Parameters | A pointer to a Stack.                                                                     |
| Return Value     | A void pointer to the element that was popped.                                            |
| Notes            | This function should pop an element off the top of the stack and return a pointer to it.  |

| **Requirement**  | **Conditions**                                                                            |
| :--------------- | :---------------------------------------------------------------------------------------- |
| Function         | void\* stack\_peek(Stack\*)                                                               |
| Input Parameters | A pointer to a Stack.                                                                     |
| Return Value     | A void pointer to the element on the top of the stack.                                    |
| Notes            | This function should return a pointer to the element on the top of the stack.             |

| **Requirement**  | **Conditions**                                                                            |
| :--------------- | :---------------------------------------------------------------------------------------- |
| Function         | int stack\_size(Stack\*)                                                                  |
| Input Parameters | A pointer to a Stack.                                                                     |
| Return Value     | An integer representing the number of elements in the stack.                              |
| Notes            | None.                                                                                     |

| **Requirement**  | **Conditions**                                                                            |
| :--------------- | :---------------------------------------------------------------------------------------- |
| Function         | bool stack\_contains(Stack\*, void\*)                                                     |
| Input Parameters | A pointer to a Stack and a void pointer to an element.                                    |
| Return Value     | True if the given item is in the stack. Otherwise false.                                  |
| Notes            | None.                                                                                     |

| **Requirement**  | **Conditions**                                                                            |
| :--------------- | :---------------------------------------------------------------------------------------- |
| Function         | bool stack\_destroy(Stack\*)                                                              |
| Input Parameters | A pointer to a Stack.                                                                     |
| Return Value     | True if the stack is successfully deallocated. Otherwise false.                           |
| Notes            | This function should deallocate any remaining elements and then the stack itself.         |

### Postconditions

Your program should be capable of producing and destroying Stack (_Stack) structures. All of the functions should be capable of
executing without crashing. Failure states should be handled by return
values. If a function with a void return type fails, it does not need to
be reported.  

### Restrictions

None.

### File Requirements

This contract requires you to provide a C source file named `stack.c`
and a C header file named `stack.h`. Your header files should contain
your forward declarations, struct definitions and typedefs, as well as
any library imports (includes) you may need. Always protect your header
with a define guard. Your source files must not contain any main
functions, or your program will fail during testing.

In addition to the C files, you will also be required to make a Makefile
for the **stack** program. Your program will be compiled by executing
**make**. Your Makefile should produce both a `stack.o` file and a
**stack** executable file by compiling your code with the `stackM.o`
file located in `CI/objects/stack`.

Your source, header, and make files should be placed in the
`Lab6/stack/` directory in your GitLab repository.

### Testing

To test your code, you can compile your source files with the
`stackM.o` object file found in `CI/objects/stack`. Your program can
then be executed as normal. The object file contains a main function, so
you do not need to provide your own when you submit to GitLab. Using a
Makefile for compiling these files together can save you a lot of time.

### Sample Inputs and Outputs

A sample output is provided, but is not used in a comparison when
executing your pipeline. The main object file for this program will test
your various functions on a stack. Your code should minimally be able to
complete the test main function in the object file, but you may find it
more convenient to test your functions with your own main function
first.

## Binary Tree

### Problem

You must create a structure and set of functions for managing a binary
tree.

### Preconditions

You are required to write a program for handling binary trees. This
consists of `bintree.c`, which should contain all of your function
implementations, and , which should contain your structure definitions,
any necessary typedefs, and all of your forward function declarations.
When you compile, you will need to include the source file in your
command in order to ensure the functions exist during the linking
process. You may include any additional helper functions as you see fit.
Since you are dealing with pointers, you will need to check all of your
pointers to ensure they are not null. Trying to perform operations on
null will lead to segmentation faults or other program crashes at
run-time.

Your binary tree will hold a specific data type (and that data type
only) as defined by the initialization parameters. The size of the data
type held is provided, as is the name. Each value stored in the binary
tree should be of the given size in bytes. For example, if your binary
is initialized as an **int** binary tree, then the item size will be
$`4`$ and the type name will be *"int"*.

Your binary tree will contain a series of pointers to structs we will
call nodes. Nodes contain the data held at that position in your binary
tree, as well as pointers to two child nodes. It is possible for nodes
to contain null values for their pointers depending on the structure of
your binary tree, so be careful not to accidentally do any work on null
pointers you don’t intend to.

Whenever a function below inserts or removes data, you will need to
create or destroy any nodes as necessary in order to keep the storage
process hidden. This means that elements will be sent into the function
and you will be required to create a node to contain them, while
ensuring the various child pointers are managed properly. It is
important to very carefully manage the state of the pointers in your
binary tree so that you do not accidentally create cycles or dangling
pointers.

The details of the binary tree functionality are described in the
**Binary Trees** section of this document. The **bool** type referenced
in this contract is found in `<stdbool.h>`. You are expected to do
basic error checking (such as checking for null pointers).

You will notice below a variety of functions which begin with an
underscore _). These functions are meant to be used interally only
(only inside bintree functions) and are not technically meant for
regular users to use. Typically these functions serve as recursive
helper functions for the main binary tree functions, in order to make
the forward-facing function list more intuitive while providing an easy
interface behind the scenes for recursive functions. During the testing
process, we are likely to test these functions on our own data types to
ensure the requirements have been met.

Your **bintree** program must include the following struct (typedef-ed
appropriately):

| **Structure Name**                     | **Fields**                      | **Functionality**                |
| :------------------------------------- | :------------------------------ | :------------------------------- |
| \_BinTreeNode (typedef BinaryTreeNode) | void\* data                     | The data held by this node.      |
|                                        | struct \_BinTreeNode\* left     | The left child of this node.     |
|                                        | struct \_BinTreeNode\* right    | The right child of this node.    |
| \_BinaryTree (typedef BinaryTree)      | BinaryTreeNode\* top            | The root node of this tree.      |
|                                        | int itemSize                    | The size of the data type held by this binary tree in bytes.    |
|                                        | char\* type                     | The name of the data type held by this binary tree as a string. |
|                                        | int (\*compare)(void\*, void\*) | A pointer to a compare function. |
|                                        | void (\*print)(void\*)          | A pointer to a print function.   |

You may have noticed that the type of the next and prev pointers in the
BinaryTreeNode struct are actually **struct \_BinTreeNode**. This is to
allow the \_BinTreeNode structure to contain itself. You won’t be able
to easily typedef the structure before it’s defined, so you have to use
**struct \_BinTreeNode** to define the pointers. Don’t worry, however.
You can still treat them as a BinaryTreeNode (by name) after the typedef
is created.

You will notice there are a lot of functions. **About half of them are
helper functions, meaning that in practice there are only about half
here that will require any coding!** The other half will simply make a
function call to the helper functions. These are designed this way to
provide a cleaner interface for the user.


Your **bintree** program must include the following functions:

| **Requirement**  | **Conditions**                                                                             |
| :--------------- | :----------------------------------------------------------------------------------------- |
| Function         | BinaryTree\* bintree\_initialize(int, char\*, int (\*)(void\*, void\*), void (\*)(void\*)) |
| Input Parameters | An integer representing a type size, a char pointer representing a type name, a function pointer to a int(void\*,void\*) comparison function, and a function pointer to a void(void\*) print function.   |
| Return Value     | A pointer to an initialized BinaryTree.                                                    |
| Notes            | This function should create and store a binary tree with the appropriate fields and a NULL root node.                                                               |

| **Requirement**  | **Conditions**                                                                             |
| :--------------- | :----------------------------------------------------------------------------------------- |
| Function         | BinaryTreeNode\* bintree\_create\_node(int, void\*)                                        |
| Input Parameters | An integer representing a data size and a void pointer to an element.                      |
| Return Value     | A binary tree node with null child pointers and the data set to match the element.         |
| Notes            | None.                                                                                      |

| **Requirement**  | **Conditions**                                                                             |
| :--------------- | :----------------------------------------------------------------------------------------- |
| Function         | bool bintree\_insert(BinaryTree\*, void\*)                                                 |
| Input Parameters | A pointer to a BinaryTree and a void pointer representing an element.                      |
| Return Value     | True if the element was inserted successfully. Otherwise false.                            |
| Notes            | None.                                                                                      |

| **Requirement**  | **Conditions**                                                                             |
| :--------------- | :----------------------------------------------------------------------------------------- |
| Function         | bool bintree\_search(BinaryTree\*, void\*)                                                 |
| Input Parameters | A pointer to a BinaryTree and a void pointer representing an element.                      |
| Return Value     | True if the element exists in the binary tree. Otherwise false.                            |
| Notes            | None.                                                                                      |

| **Requirement**  | **Conditions**                                                                             |
| :--------------- | :----------------------------------------------------------------------------------------- |
| Function         | void bintree\_print\_in\_order(BinaryTree\*)                                               |
| Input Parameters | A pointer to a BinaryTree.                                                                 |
| Return Value     | None.                                                                                      |
| Notes            | Print the binary tree following the in-order traversal requirements.                       |

| **Requirement**  | **Conditions**                                                                             |
| :--------------- | :----------------------------------------------------------------------------------------- |
| Function         | void bintree\_print\_pre\_order(BinaryTree\*)                                              |
| Input Parameters | A pointer to a BinaryTree.                                                                 |
| Return Value     | None.                                                                                      |
| Notes            | Print the binary tree following the pre-order traversal requirements.                      |

| **Requirement**  | **Conditions**                                                                             |
| :--------------- | :----------------------------------------------------------------------------------------- |
| Function         | void bintree\_print\_post\_order(BinaryTree\*)                                             |
| Input Parameters | A pointer to a BinaryTree.                                                                 |
| Return Value     | None.                                                                                      |
| Notes            | Print the binary tree following the post-order traversal requirements.                     |

| **Requirement**  | **Conditions**                                                                             |
| :--------------- | :----------------------------------------------------------------------------------------- |
| Function         | void bintree\_print\_reverse\_order(BinaryTree\*)                                          |
| Input Parameters | A pointer to a BinaryTree.                                                                 |
| Return Value     | None.                                                                                      |
| Notes            | Print the binary tree following the reverse-order traversal requirements.                  |

| **Requirement**  | **Conditions**                                                                             |
| :--------------- | :----------------------------------------------------------------------------------------- |
| Function         | bool \_bintree\_insert\_recursive(BinaryTree\*, BinaryTreeNode\*, void\*)                  |
| Input Parameters | A pointer to a BinaryTree, a pointer to a BinaryTreeNode, and a void pointer representing an element.                                                                   |
| Return Value     | True if the function successfully inserted the element to the tree. Otherwise false.       |
| Notes            | This function should be called by the *bintree\_insert* function to aid in the recursive traversal process. This function will do the majority of the inserting.          |

| **Requirement**  | **Conditions**                                                                             |
| :--------------- | :----------------------------------------------------------------------------------------- |
| Function         | bool \_bintree\_search\_recursive(BinaryTree\*, BinaryTreeNode\*, void\*)                  |
| Input Parameters | A pointer to a BinaryTree, a pointer to a BinaryTreeNode, and a void pointer representing an element.                                                                   |
| Return Value     | True if the function successfully finds the element in the tree. Otherwise false.          |
| Notes            | This function should be called by the *bintree\_search* function to aid in the recursive traversal process. This function will do the majority of the searching.          |

| **Requirement**  | **Conditions**                                                                             |
| :--------------- | :----------------------------------------------------------------------------------------- |
| Function         | void \_bintree\_in\_order\_recursive(BinaryTree\*, BinaryTreeNode\*)                       |
| Input Parameters | A pointer to a BinaryTree and a pointer to a BinaryTreeNode.                               |
| Return Value     | None                                                                                       |
| Notes            | This function should be called by the *bintree\_print\_in\_order* function to aid in the recursive traversal process. This function will do the majority of the traversal and will print the values accordingly.                                                     |

| **Requirement**  | **Conditions**                                                                                |
| :--------------- | :-------------------------------------------------------------------------------------------- |
| Function         | void \_bintree\_pre\_order\_recursive(BinaryTree\*, BinaryTreeNode\*)                         |
| Input Parameters | A pointer to a BinaryTree and a pointer to a BinaryTreeNode.                                  |
| Return Value     | None                                                                                          |
| Notes            | This function should be called by the *bintree\_print\_pre\_order* function to aid in the recursive traversal process. This function will do the majority of the traversal and will print the values accordingly.                                                        |

| **Requirement**  | **Conditions**                                                                                |
| :--------------- | :----------------------------------------------------------------------------------------- |
| Function         | void \_bintree\_post\_order\_recursive(BinaryTree\*, BinaryTreeNode\*)                        |
| Input Parameters | A pointer to a BinaryTree and a pointer to a BinaryTreeNode.                                  |
| Return Value     | None                                                                                          |
| Notes            | This function should be called by the *bintree\_print\_post\_order* function to aid in the recursive traversal process. This function will do the majority of the traversal and will print the values accordingly.                                                        |

| **Requirement**  | **Conditions**                                                                                |
| :--------------- | :----------------------------------------------------------------------------------------- |
| Function         | void \_bintree\_reverse\_order\_recursive(BinaryTree\*, BinaryTreeNode\*)                     |
| Input Parameters | A pointer to a BinaryTree and a pointer to a BinaryTreeNode.                                  |
| Return Value     | None                                                                                          |
| Notes            | This function should be called by the *bintree\_print\_reverse\_order* function to aid in the recursive traversal process. This function will do the majority of the traversal and will print the values accordingly.                                                        |

### Postconditions

Your program should be capable of producing BinaryTree (_BinaryTree)
structures. All of the functions should be capable of executing without
crashing. Failure states should be handled by return values. If a
function with a void return type fails, it does not need to be
reported.

During testing, expect the testing script to iterate through the
underlying nodes in your BinaryTree struct manually in order to verify
their contents and size.

### Restrictions

None.

### File Requirements

This contract requires you to provide a C source file named
`bintree.c` and a C header file named `bintree.h`. Your header files
should contain your forward declarations, struct definitions and
typedefs, as well as any library imports (includes) you may need. Always
protect your header with a define guard. Your source files must not
contain any main functions, or your program will fail during testing.  
In addition to the C files, you will also be required to make a Makefile
for the **bintree** program. Your program will be compiled by executing
**make**. Your Makefile should produce both a `bintree.o` file and a
**bintree** executable file by compiling your code with the
`bintreeM.o` file located in `CI/objects/bintree`.

In addition to the regular main object file, there are four additional
main object files, one for each type of traversal function (in, pre,
post, rev). Your make file must also compile those main objects with
your `bintree.o` file to produce the **intree**, **pretree**,
**posttree**, and **revtree** executables. We suggest you set up a
target which requires each of those files to be made, then set up a
target for each of them as appropriate. All the main object files are
located in the `CI/objects/bintree` directory.

Your source, header, and make files should be placed in the
`Lab6/bintree/` directory in your GitLab repository.

### Testing

To test your code, you can compile your source files with the
`bintreeM.o` object file found in `CI/objects/bintree`. Your program
can then be executed as normal. The object file contains a main
function, so you do not need to provide your own. Using a Makefile for
compiling these files together can save you a lot of time.

As mentioned above, you will also need to execute the other main object
files found in the `CI/objects/bintree` objects directory. Each
traversal test file adds 10,000 values to an integer binary tree and
then tests a given traversal. The expected outputs are found in the
objects directory and are used to compare against your own outputs to
ensure your traversals are working properly during the pipeline
execution.

### Sample Inputs and Outputs

All sample outputs are provided in the relevant objects directory. The
main object files for this program will test your various functions on
an int binary tree. Your code should minimally be able to complete the
test main functions in the object files, but you may find it more
convenient to test your functions with your own main function first.

# Submission

## Required Files

Each file must be contained in the directory listed in the structure
requirement diagram below. These files include:

1.  `queue.c`
2.  `queue.h`
3.  `stack.c`
4.  `stack.h`
5.  `bintree.c`
6.  `bintree.h`
7.  `Makefile` (for queue)
8.  `Makefile` (for stack)
9.  `Makefile` (for bintree)

## Submission Procedure and Expectations

Your code will be submitted to your Lab 6 GitLab repository using the
same method as outlined in the Lab Technical Document. Refer to that
document if you do not remember how to submit files via the GitLab
service. A link to your repository can be found in the `Lab6` subgroup
of the CSCI 2122 GitLab group
[<span style="color: blue">here</span>](https://git.cs.dal.ca/courses/2022-fall/csci-2122).  
As mentioned in the Lab Technical Document, we will provide you with a
CI/CD script file which will help you test your submissions. The .yml
file containing the CI/CD test script logic, and any other necessary
script files, are available in your repository at all times. You are
free to view any of the script files to help you understand how our
testing scripts will function. We make extensive use of relative path
structures for testing purposes, which is why strict adherence to
directory structure and file contents is such a necessity. Also remember
to check your pipeline job outputs on the GitLab web interface for your
repository to see where your jobs might be failing.

Remember to follow the instruction guidelines as exactly as possible.
Sometimes the pipeline scripts will not test every detail of your
submission. **Do not rely on us to perfectly test your code before
submission.** The CI/CD pipeline is a great tool for helping you debug
major parts of your submissions, but you are still expected to follow
all rules as they have been laid out.

## Submission Structure

In order for a submission to be considered valid, and thus testable,
your git repository must contain directories and files in the following
structure:  

```plaintext
Lab6/
 ┣ queue/
 ┃  ┣ queue.c
 ┃  ┣ queue.h
 ┃  ┗ Makefile
 ┣ stack/
 ┃  ┣ stack.c
 ┃  ┣ stack.h
 ┃  ┗ Makefile
 ┗ bintree/
    ┣ bintree.c
    ┣ bintree.h
    ┗ Makefile

```

As with all labs, accuracy is incredibly important. When submitting any
code for labs in this class, you *must* adhere to the directory
structure and naming requirements in the above diagram. Failure to do so
will cause the testing pipeline to fail. That said, in this lab, your
directory structure requirement is to *minimumally* have these files,
but you may have more as you require.

Remember to remove `Lab6/delete_this_file` from your repository
using <kbd>git rm</kbd> to avoid any pipeline failures.
