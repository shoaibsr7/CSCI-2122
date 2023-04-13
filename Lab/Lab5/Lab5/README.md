# Introduction

This lab is designed to introduce you to makefiles, array lists, and
linked lists. By the end of this lab, you will be expected to understand
those concepts.

In this lab you are expected to perform the basics of cloning your Lab 5
repository from the GitLab course group. A link to the course group can
be found
[<span style="color: blue">here</span>](https://git.cs.dal.ca/courses/2022-fall/csci-2122)
and your repository can be found in the Lab5 subgroup. See the Lab
Technical Document for more information on using git. You will notice
that your repository has a file in the `Lab5` directory named
`delete_this_file`. Due to the limitations of GitLab, we are not
able to push completely empty directories. Before your push your work to
your repository (which should be in the `Lab5` directory anyway), make
sure to first use the <kbd>git rm</kbd> command to remove the extra file. If
you do not, your pipeline will fail.  

**Be sure to read this entire document before starting!**

# Table of Contents
[[_TOC_]]


# Makefiles

Are you sick of typing out really long **gcc** commands to compile your
code? Do you press the up arrow a dozen times to find your last **gcc**
command, so you can run it again? If this sounds like you, then have I
got a deal for you! It’s called the **make** utility and you and your
family are going to love it!

## The make Utility

The make utility is a Unix command which is capable of managing your
files during the compilation process. It can be used with any
programming language whose compiler can be run with a shell command,
including C.

When executed, **make** automatically searches the directory it’s
contained in for a file named *Makefile*. A makefile lets you organize a
series of compilation commands into a series of conditions and
requirements. By describing the relationships among files in a program,
and defining the requirements for keeping your various compiled code
files up-to-date, **make** can run through your source files from the
top down in order to guarantee all of your code compiles properly, with
the shortest path to success possible.

The make utility only updates compiled code which needs updating. If no
changes have been made to the source code, make won’t attempt to compile
that file again. This can drastically reduce compilation times and help
alleviate excessive use of computing resources, especially in large
projects.

In the context of C, there are only two conditions under which **make**
will (re)compile a file:

1.  A .c file was modified more recently than its associated .o file (meaning that changes have been made to the .c file since last compilation).
2.  There is no .o file present for a given .c file.

You should write your makefile in a way such that it produces a .o file
for every .c file you use. Failure to do so wastes computer resources
and time on recompiling files that don’t need to be compiled again. At
this point, you may have an understanding that .o files contain machine
code which has not yet been linked into an executable program. You’ve
been using .o files to handle compiling our main functions for testing
your programs. By always creating .o files from your source code, you
will only need to compile code which has been updated, while the
remaining .o files stand by, ready to be immediately linked.

In addition to keeping your code in object files which are ready for
compilation, make also offers you the ability to manage your code
structure in other ways. For example, if you want to force **make** to
recompile your entire project, including the executable file, you can
use the command **make clean**. This is a specific goal which you must
define in your makefile, but is a common convention for creating a fresh
environment to compile with. You can find instructions for creating a
**clean** rule below.

## Makefile Syntax

### Comments

Comments in makefiles start with a octothorpe (also referred to as a
pound sign or hashtag). These lines are ignored during the make process
and can be used to help identify individual components of your Makefile.

``` bash
# This is a comment.
```

### Variables

All variables are strings. By convention, variable names are uppercase.
Accessing variables is done using a dollar sign, followed by the
variable name surrounded by parentheses.

``` bash
# Declare a variable.
VARIABLE = some string

# Access the variable.
$(VARIABLE)
```

### Rules

Rules are the core functionality of makefiles. Rules define what to
compile and how to compile it. A rule consists of three parts: the
target, the prerequisites, and the commands (or recipe).  
The **target** is the file you are trying to produce through
compilation, whether that be a .o file or an executable file.

**Prerequisites** are the files that need to be compiled **before the
current target can be compiled** (or at least the files that must exist
in order for the compilation to succeed). The target file depends on
these files (usually .o or .c files). You should also note that **make**
will try to compile any C source files that are given as prerequisite
files, even if you do not define a rule for those files. You should not
let **make** decide how to compile something. Always define a rule for
it instead!  


**Commands** are the Unix commands you want **make** to execute.
Usually, you’d put the commands needed to compile the target file.
However, you can put any Unix command in this section. It is important
to note that commands **must** start with a tab character. Failure to do
so will produce errors and unexpected results.

Rules are executed starting from the first rule in your file. This rule
is called the **default rule** or **default goal**. When you run make,
it will move to the first rule and attempt to complete the target based
on the prerequisites and commands you provide. If that rule has
prerequisites, make will try to compile each of them (if they are .c or
.o files), or simply check that they exist. If your default target does
not contain any prerequisites, it will simply try to run it on its own.
You may also set up additional rules which are not in the prerequisites
of other targets, thus allowing for multiple chains of execution.

When make tries to run a rule, it checks to see if the target exists. If
it does, it checks the prerequisites for that file and determines if the
current target is older than the source it was compiled from. If the
source is newer than the target (there are changes since the target was
compiled), it will execute the rule. If not, then it will skip the
rule’s execution and move on to the next valid rule in the current
make execution. If it has nothing else to execute, make will finish
successfully.

If you want to run a specific target, you can execute it by name with
**make TARGET\_NAME**.

The following code block illustrates the generic structure of a rule.

``` bash
target : prerequisites
    command
    command
    command
```

### The clean Rule

**clean** is a rule which is used as something of a common convention.
Since we can technically define targets which are not files, we can
define the clean target, which will dictate what happens when you enter
**make clean** from the terminal. As a good starting point, **clean**
should remove the .o and executable files generated by the Makefile.
Here we use the **-f** option on the rm command to stop it from asking
us to remove files (AKA force removal). Obviously, this should be done
with caution.

``` bash
clean : 
    rm -f file1.o file2.o executablefile
```

## A Simple Example

In this example, we are going to start by writing a very rudimentary
Makefile, then refactor that example until we have a comprehensive
Makefile that is both usable, and computationally efficient.

We will start this example by assuming you have a file called
**code.c**, which contains function definitions; a header file called
**code.h**, which contains forward declarations for the functions in
**code.c**; and a file called **main.c**, which contains a main
function. In this example, you’re hoping to compile this code so that
the resultant executable file is named **runme**. In this case, the
**target** is runme, the **prerequisites** are main.c and code.c, and
the "**commands**" are just one command: **gcc**.

``` bash
# Rule for compiling runme.
runme : code.c main.c
    gcc --std=c18 code.c main.c -o runme
```

To optimize compilation, you should change the prerequisites to **main.o
code.o**. However, this means that both files will require a rule, as
our Makefile does not understand how we want to generate those object
files without telling it how to do so. If we don’t tell it what to do,
it will use the most basic form of gcc compilation (with a **-c**
option) to attempt to create the object files, which may or may not
work. With this in mind, we should then create our Makefile to include
rules for runme, code.o, and main.o.

``` bash
# Rule for compiling runme.
runme : code.o main.o
    gcc --std=c18 code.o main.o -o runme

# Rule for compiling code.c to code.o.
code.o : code.c code.h
    gcc --std=c18 -c code.c     

# Rule for compiling main.c to main.o.
main.o : main.c code.h
    gcc --std=c18 -c main.c
```

To give some context to the rules, let’s examine the rule for
**code.o**. To start, the code.o file is a **pre-compiled binary object
file** made by **gcc**. Precompiled binary object files are very useful
because they are already compiled, but not yet linked, by the compiler.
As long as we have these files, we can speed up the compilation process
by not always fully recompiling every source code file, which is the
**code.c** file in this case. Instead, our motivation with **make** will
be that we only want to re-compile code.o if the code.c file has been
updated since the last time we compiled the code.o file. By doing this,
we only compile files when we need to because if our source code hasn’t
changed, why compile the whole thing over and over again every time?
Since the **make** program checks the timestamps of the prerequisites,
it can determine (based on when the prerequisites were last edited)
whether or not this rule actually needs to execute.

When the rule is executed, **make** checks the prerequisites, one at a
time. If a prerequisite has a rule, it will attempt to run it and follow
the same pattern on that rule. If it doesn’t have a rule, it will check
if the prerequisite exists as a file, and if it does then it checks to
see if the prerequisite is newer than the target file. If the
prerequisite is newer, this rule has to re-execute. If none of the
prerequisites are newer (or none of their associated rules needed to
execute to produce new files), then this rule does not need to execute
because the file is as new as it can be. The **make** program would then
stop executing this rule and go back to the calling rule, which would be
the **runme** target.

Next, we’ll introduce some variables. Parts of the command are fairly
short things to turn into variables, but obviously you don’t want to
have to change “gcc” in every rule if you ever wanted to change your
compiler. You can use a variable to hold the string "gcc", and another
variable to hold the string "`--std=c18`".

``` bash
# Define the compiler to use. 
COMPILER = gcc

# Define the C standard to use.
CSTD = --std=c18

# Rule for compiling runme.
runme: code.o main.o
    $(COMPILER) $(CSTD) code.o main.o -o runme

# Rule for compiling code.c to code.o.
code.o: code.c code.h
    $(COMPILER) $(CSTD) -c code.c     

# Rule for compiling main.c to main.o.
main.o: main.c code.h
    $(COMPILER) $(CSTD) -c main.c
```

Finally, you can add a clean rule, in case you want to remove all of
your .o files, and the executable file. If you execute **make clean**,
then the next time you use **make**, the make utility will recompile all
of your .c files (assuming your clean rule is set up properly). This
helps you do a quick "reset" if you want to start compilation from
scratch.

``` bash
# Define the compiler to use. 
COMPILER = gcc

# Define the C standard to use.
CSTD = --std=c18

# Rule for compiling runme.
runme: code.o main.o
    $(COMPILER) $(CSTD) code.o main.o -o runme

# Rule for compiling code.c to code.o.
code.o: code.c code.h
    $(COMPILER) $(CSTD) -c code.c     

# Rule for compiling main.c to main.o.
main.o: main.c code.h
    $(COMPILER) $(CSTD) -c main.c

# Clean rule.
clean :
    rm -f code.o main.o runme
```

## Example of a Makefile for Pascal

In this example, we will discuss the various ways to create a makefile
for the Pascal problem of Lab 3. In case you need a refresher, the
(relevant) file structure for Lab 3 was:

Before you compiled pascal.c, you needed to include your mmath library.
You may have copied the mmath.c, mmath.h, and pascalM.o files to your
pascal directory, (which is perfectly fine) but this example will assume
you did not make such copies.

Your gcc command likely would have looked something like this:  


```plaintext
gcc –std=c18 -lm -I../lib -o pascal exe ../../CI/objects/pascal/pascalM.o pascal.c ../lib/mmath.c ../lib/mstring.c
```

Instead of typing that, we could use a Makefile.  
We’ll start like we did in the previous example, and place the "gcc"
command, as-is, into a makefile.

``` bash
# This is terrible. Don't do this. Line 3 doesn't even fit on one line. 
pascal_exe: ../lib/mmath.c ../lib/mstring.c pascal.c ../../CI/objects/pascal/pascalM.o
    gcc --std=c18 -lm -I../lib -o pascal_exe ../../CI/objects/pascal/pascalM.o pascal.c ../lib/mmath.c ../lib/mstring.c
```

To make this more readable, we can break each section of the compiler
command down into a relevant variable. Let’s add those variables:

``` bash
# Define which compiler to use. 
COMPILER = gcc

# Define which C standard to use.
CSTD = --std=c18

# Define paths to other header files we need to use.
INCLUDES = -I../lib

# Define any library flags, such as -lm.
LIBFLAGS = -lm

# Define the path to the file with the main function.
MAIN = ../../CI/objects/pascal/pascalM.o

# Rule for pascal_exe
pascal_exe: ../lib/mmath.c ../lib/mstring.c pascal.c $(MAIN)
    $(COMPILER) $(CSTD) $(LIBFLAGS) $(INCLUDES) $(MAIN) pascal.c ../lib/mmath.c ../lib/mstring.c -o pascal_exe
    
```

You can see that our command for the pascal_exe rule is still pretty
long. Let’s break it down further by adding some more rules and
variables:

``` bash
# Define which compiler to use. 
COMPILER = gcc

# Define which C standard to use.
CSTD = --std=c18

# Define paths to other header files we need to use.
INCLUDES = -I../lib

# Define any library flags, such as -lm.
LIBFLAGS = -lm

# Define the path to the file with the main function.
MAIN = ../../CI/objects/pascal/pascalM.o

# Define the path to mmath.c and mmath.h.
MMATH = ../lib/mmath.c ../lib/mmath.h

# Define the path to mstring.c and mstring.h.
MSTRING = ../lib/mstring.c ../lib/mstring.h

# Define the .o files needed to compile pascal_exe.
PREREQUISITES = mmath.o mstring.o pascal.o

# Rule for pascal_exe
pascal_exe: $(PREREQUISITES) $(MAIN)
    $(COMPILER) $(CSTD) $(LIBFLAGS) $(INCLUDES) $(MAIN) $(PREREQUISITES) -o pascal_exe

# Rule to compile pascal.c to pascal.o. 
pascal.o: pascal.c pascal.h
    $(COMPILER) $(CSTD) $(LIBFLAGS) $(INCLUDES) -c pascal.c

# Rule to compile mmath.c to mmath.o
mmath.o: $(MMATH)
    $(COMPILER) $(CSTD) $(LIBFLAGS) -c ../lib/mmath.c

# Rule to compile mstring.c to mstring.o
mstring.o: $(MSTRING)
     $(COMPILER) $(CSTD) $(LIBFLAGS) -c ../lib/mstring.c

# Clean rule.
clean: 
    rm -f $(PREREQUISITES) pascal_exe
```

This is a fairly well-structured Makefile. Placing these variables and
rules into a file called "Makefile" in your pascal directory from Lab 3
will allow you to run **make** and **make clean** in your pascal
directory to compile your code with just some simple commands.

# Array Lists

In this lab you will be creating a data structure referred to (in Java)
as an array list. You may see these data structures referred to by a
variety of names, including vectors, dynamic arrays, or mutable arrays,
but we will stick with the Java naming convention just for the sake of
familiarity. We will use the word "array" to often mean "pointer to a
memory block", even though arrays and pointers are not exactly the same
thing.

Array lists are a specific type of structure which maintains an array
internally and grows that array as required by the content. This allows
the array to maintain a particular amount of empty space in order to
accommodate increasing amounts of data. As you add data to your array
list, it will grow toward some preset number of elements (as arrays have
a fixed length). Once your array list has something added to it which
would fall off the end of the range of its internal array, it will
automatically resize the array by some fixed scalar known as a **growth
factor**. The growth factor of array lists vary by programming language,
but a basic growth factor is 2, with alternatives existing in the
compiler world. For example, the **ArrayList** class in Java uses a
growth factor of 3/2, or 1.5. The Rust **vec** type uses a growth factor
of 2.

There are debates about what the most useful growth factor is, with 1.5
allowing the reuse of old memory blocks by eventually allowing the
"remainder" of a variety of memory resizes to equal a full memory block
width (thus making it reusable by the system), while still other
frameworks, such as Microsoft .NET, use a doubling factor with an
increase to the next prime, in order to better space their hash values
for buckets. For the sake of simplicity, in this implementation we will
use a growth factor of 2.

In this lab, you will be expected to provide a definition for an Array
List which matches the specifications below.

## Creating an Initial Array List

Your array list implementation will be using a struct to contain the
data most relevant to an array list. Since C cannot dynamically type the
data your array list holds in a simple way, you will need to store data
in each array location as a void pointer (void\*). Generally, the void
type refers to a lack of type and is often associated exclusively with
*nothing*. However, we can create void pointers (void\*) which , instead
of dealing with nothing, instead allow you to hold a memory block with
no type. Any data stored in a void pointer is considered generic
byte-stored data and you can’t do anything with it without telling C to
treat it as a valid data type (aside from void\*). Since any information
about the data you’re storing in a void pointer will be lost, you also
need to keep track of **the data’s size** and **the data’s type**, which
will be included as fields in your struct.

In addition to the data being stored, the array list must also have an
understanding of both it’s **maximum size** and it’s **current size**.
Since an array list is dynamically allocated based on its growth factor
of 2, your array will have a maximum size, but not all of the array
indexes will be filled with data. As a general rule, your array is only
as long as the explicit data it holds and should never store a NULL
pointer as a valid element. Rather than making an index within the
explicit data NULL, you will instead remove it from the array
completely. This means your array list, starting from index 0, must have
data in every position up to the *size-1* index, after which the indexes
are ignored until another element is added.

When you create your initial ArrayList struct, it should have field for
an initial maximum size defined by the user $`(maxSize)`$, a field for
an initial current size of 0 $`(size)`$, an initial data type $`(type)`$
and data type size $`(itemSize)`$ provided by the user, with an array
$`(arr)`$ allocated enough memory to contain $`maxSize`$ void pointers.

## Adding Elements to an Array List

You will need to write a series of functions for adding values to the
array list. The first rule of adding to an array list is that an element
may only be added between of the ends of the current list, which is
always in $`[0, size]`$. Adding an element to a position inside the
range $`[0, size-1]`$ will insert the incoming value *before* the
element in the current index. This will force all elements after the
current index (and including it) to move one to the right. If you
attempt to add an element to the end of the list, it will be inserted in
an index equal to the current $`size`$ value.

All values added to the array list should be **copies** of the original
values. You should not save the original pointers. You will need to
allocate an amount of space based on the $`itemSize`$, then copy the
element into that memory space. The string.h library has a function
called **memcpy** which can be used to copy the data in a void pointer
to another void pointer.

Every time an element is successfully added, the $`size`$ value of the
array list should increase by 1. If there is an attempt to add an
element to an invalid index, the add should not proceed. If an element
should be added, but $`size == maxSize`$, then the array list should be
resized before the add is completed.

## Removing Elements from an Array List

You will need to write a function for removing a value from a specific
index. Whenever a remove is attempted, the index should be in
$`[0, size-1]`$. If it is not, then the remove should not proceed. Since
our array lists only grow larger, there is never a need for you to
resize an array list to be smaller when removing an element from the
list. To remove an element from a list, you can deallocate the data at
the given index, then iterate through $`[index+1, size-1]`$ to move
every value to the left. When the remove is completed, $`size`$ should
decrease by 1.

## Clearing an Array List

You will need to write a function for clearing the array list. Clearing
an array list is as simple as freeing every index in $`[0, size-1]`$ and
then setting the $`size`$ value to 0.

## Getting an Element from an Array List

You will need to write a function for returning an element from the list
at a given index. Make sure the index is within the bounds of the
array’s current size. You will need to return a copy of the void
pointer to the data, and it is up to the user to store it in a data type
that they’re expecting from the list.

## Finding the Index of an Element in an Array List

You will need to write a function which returns the index of a given
element in your array list. To achieve this, you must iterate through
the list and compare each element to the provided value. The string.h
library has a function called **memcmp** which can be used to compare
the first $`n`$ bytes of data in two void pointers. If the element is
found in the list, you should return the index where it is located. If
the element is not found, return $`-1`$.

## Destroying an Array List

You will need to write a function which destroys an array list. Your
function should free every element in your array list, free the array,
free the stored data type, then free the entire ArrayList.

## Resizing an Array List

Finally, you will need to write a function which resizes an array list.
As mentioned above, when $`size == maxSize`$, you will need to increase
the size of the array stored in your array list structure. To do that,
you can multiply the maximum size by the growth factor of 2 and then use
**realloc** to reallocate the amount of memory currently stored in your
array. Remember to also account for the size of the things stored in
your array (void pointers) when calculating the new maximum size.

## Interacting with an Array List

When using your array list, it is not necessary to cast it to a type
every time. Doing so will clutter your code and make it far less
readable, as using a returned value in place (if your array list holds
integers, for example) would require something ugly like
**$`*((int*)alist\_get(arrayList, 3))`$**. Instead, create a pointer
variable of the type you’d like to use and always return values into it.
Since your array list functions will return void pointers, they will
always automatically defer to the type they are being stored in. After
your pointer is stored, it should only require a simple dereference to
use it in the future.

Your array list will store a data type as a string (char\*), which you
can access any time, as well as the size of that data type. You can
access these at any time to determine how to best use your array list.
It will be helpful for understanding how much your variables should
allocate, which array list (if you have multiple) is holding which type
of value, etc.

# Linked Lists

Linked lists are a classic data structure which is capable of managing
data without explicitly needing to allocate an array. Instead of
adhering to standard indexing, linked lists create a chain of smaller
data structures called **Nodes**, which contain two fields: the **data**
to be stored and a **pointer** to the next node in the list. A standard
linked list operates such that a node begins a chain of pointers which
pass through other nodes in order. Eventually, by stepping through all
of the nodes, you will reach the final node which has a pointer
terminating to NULL. If you add another node to the end of that chain,
the last node in the chain will have its pointer changed to the new end
node, which will have its pointer terminate to NULL. As such, you get a
structure which looks like the following:

![image](CI/docs/linked_list.png)

One of the benefits of this type of list is that inserting an element
anywhere is very simple and does not require us to move data one-by-one
through array indexes when something is inserted (which can take a long
time), and we are not bound by the size of an array (which is fixed).
The linked list has the downside of requiring you to do more searching
through your list in order to find data. For example, in an array you
can jump to the $`n`$th element with a simple offset or index reference.
In a linked list, you will have to continuously step through $`n`$
pointers to find that element. However, there are some ways to overcome
the limitations of linked lists (at least partially) in order to improve
performance, and there are many applications where they are the
preferred list type.

One of the first things you can do to improve the performance of a
linked list is to maintain both a pointer to the first node and the last
node. Having access to the last node means that inserting something on
the end of the list is a very quick operation, similar to inserting
something on the front of the list. Since inserting to the front of the
list doesn’t require us to move any data in memory (as with an array,
which would need every element to move one space to the right in order
to make room for the new element), it can be done in a single step.
Adding to the end is a similar process, which makes it very fast if we
maintain a pointer to the last node.

We can use the above technique to create hassle-free stacks and queues.
By always adding and removing from the front of a linked list, we can
create a stack. Those actions are referred to pushing and popping a
stack and a linked list handles those actions very efficiently by
constantly adding or removing only the first node. Queues implemented by
linked lists are efficient for the same reason, as you always move a new
item into the front of the queue, but only ever remove items from the
end. A stack’s order of operations can be seen as "first in, last out"
(FILO), while a queue is seen as "first in, first out" (FIFO).

To make our lives easier when managing linked lists, we will implement a
doubly linked list in this lab. A doubly linked list modifies the nodes
in the list to contain a pointer both to the next node and the previous
node. This gives us extra flexibility when inserting and removing nodes
from the list by having access to forward and backward pointers for easy
insertions and removals.

![image](CI/docs/linked_list_double.png)

Whenever a new node (New) is added between two other nodes (Left and
Right) in a doubly linked list, the following steps occur:  

1.  The Left node’s next pointer points to the New node.
2.  The Left node’s prev pointer stays the same.
3.  The Right node’s next pointer stays the same.
4.  The Right node’s prev pointer points to the New node.
5.  The New node’s prev pointer points to the Left node.
6.  The New node’s next pointer points to the Right node.

This process can be seen here:

![image](CI/docs/linked_list_double_insert.png)
![image](CI/docs/linked_list_double_insert_complete.png)

When adding a node to one of the ends of the linked list, the process is
handled in largely the same fashion, but be careful about ensuring that
you have terminating NULL values where applicable, as the first node has
a prev pointer which is NULL, and the last node has a next pointer which
is NULL. When removing a node, these steps need to be followed in the
reverse of the order starting from step 4 above, with similar
considerations for the start and end of the linked list. You will not
need to alter any pointers contained in the removed node, as it should
be deallocated and its pointers lost. **However, do not deallocate the
nodes in the pointers, as this will destroy the nodes they are pointing
to! This will destroy the functionality of your linked list
immediately.**

In this lab, you will be expected to provide a definition for a Linked
List which matches the specifications below.

## Creating an Initial Linked List

Your linked list implementation will be using a struct to contain the
data most relevant to the linked list. Similar to the array list, you
will be given an integer which tells you how big each element in your
list will be in bytes (*itemSize*), as well as a string representing the
type being stored (*type*), for your reference.

The Linked List struct is an encapsulation struct which holds the data
type information, as well as a pointer to the *first* node, a pointer to
the *last* node, and the number if nodes (elements) in your linked list
(*size*). Since initializing the linked list does not actually provide
it any data, your node pointers should be set to NULL and the size of
your linked list starts at 0.

## Adding Elements to a Linked List

You will need to write a series of functions for adding values to the
linked list. There is a function for adding an element to the front of
the linked list, a function for adding an element to the end of the
linked list, and a function for adding an element at any index in the
bounds of the linked list. It’s recommended that you write the
index-based add function first, then call that function in the other
two, since you know the index values of the start and end of your
list.

When attemping to add a number to an arbitrary location via index, you
can consider that an index in this case is a number $`n`$, such that you
are returning the $`n`$th element from the start of the list,
considering the first node to be element 0. This will require you to
iterate through the linked list by continuously updating a pointer to be
equal to the next pointer of a current node. To iterate through your
linked list, use the following steps:  

1.  Create a counter, starting at 0, for the number of nodes you’ve seen.
2.  Create a Node pointer and set it to the first node pointer in the linked list.
3.  If your counter is equal to the index you’re trying to find, you’ve got a pointer to the node you need.
4.  Else set your Node pointer equal to the Node’s next pointer (Node = Node`->`next).
5.  Increase your counter by 1.
6.  Go to (3)

Effectively, you create a pointer to a Node type and store the first
node’s pointer in it. If you have not yet arrived at the $`n`$th node,
then your Node pointer should become equal to the current node’s *next*
pointer and you should increment a count by 1. Repeat this process until
you have followed enough pointers such that your counter equals the
index you’re looking for. At this point you should have the node you
require. If you end up with a NULL value in your pointer (which you
should be checking for in some way), then the index you’re looking for
is not inside the bounds of the size of the list.

All values added to the linked list should be **copies** of the original
values. You should not save the original pointers. You will need to
allocate an amount of space based on the $`itemSize`$, then copy the
element into that memory space. The string.h library has a function
called **memcpy** which can be used to copy the data in a void pointer
to another void pointer.

Remember that an empty linked list has a first and last node equal to
null, but when you add the first node, that node will be both the first
and last node. As you add more nodes, be sure to keep the first and last
pointers updated to ensure proper operation of the linked list.

Every time an element is successfully added, the $`size`$ value of the
linked list should increase by 1. If there is an attempt to add an
element to an invalid index, the add should not proceed.

## Getting an Element from a Linked List

You will need to write a function for returning an element from the list
at a given index. Similar to adding, you will have to search the list
for the element in question. Once you find it, you can return the value
stored in the node (not the node itself) as a void pointer.

## Finding the Index of an Element in a Linked List

You will need to write a function which which returns the index of a
given element in your linked list. To achieve this, you must iterate
through the linked list (using the method from the Add section above)
and compare the data held in each node to the element provided by the
function parameters. The string.h library has a function called
**memcmp** which can be used to compare the first $`n`$ bytes of data in
two void pointers. If the element is found in the list, you should
return the index where it is located. If the element is not found,
return $`-1`$.

## Removing Elements from a Linked List

You will need to write a series of functions for removing elements from
your linked list. This process is similar to the add functions, except
obviously done by removing a node rather than creating one. The
functions will need to ensure that the pointers for all nodes involved
in the removal are up-to-date. Be sure not to destroy the node before
you get the appropriate pointers from it.

## Destroying a Linked List

You will need to write a function which destroys a linked list. Your
function should free every node in the linked list, as well as all of
the data in each node. Once all of the nodes are freed, your function
should then free the type string, followed by the linked list itself.

## Interacting with a Linked List

Follow the same rules for handling data type recognition and pointers
from the array list instructions. The linked list is used in exactly the
same fashion, and all of the extra structural requirement to the data is
meant to be hidden from the user. As such, in practice, using an array
list vs. a linked list should function in an identical fashion, as far
as the shared functions are concerned.

# Lab 5 Function Contracts

In this lab you will be responsible for fulfilling two lab contracts:
the **Array List** contract and the **Linked List** contract. Each
contract is designed to test you on some of the things you’ve learned
throughout the instruction portion of this lab.

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
**git add** any of your extra main function source files.

The programs you write for this lab will not be compiled with any
additional libraries, as they should not be required.

For those of you who are concerned, when deciding which naming
conventions you want to use in your code, favour consistency in style,
not dedication to a style that doesn’t work.


## Array List

### Problem

You must create a structure and set of functions for managing an array
list.

### Preconditions

You are required to write a program for handling array lists, which
consists of `array_list.c`, which should contain all of your function
implementations, and , which should contain your structure definition,
any necessary typedefs, and all of your forward function declarations.
When you compile, you will need to include the source file in your
command in order to ensure the functions exist during the linking
process. You may include any additional helper functions as you see fit,
although they will likely not be necessary. Since you are dealing with
pointers, you will need to check all of your pointers to ensure they are
not null. Trying to perform operations on null will lead to segmentation
faults or other program crashes at run-time.

Your array list will hold a specific data type (and that data type only)
as defined by the initialization parameters. The size of the data type
held is provided, as is the name. Each element stored in the array list
should be of the given size in bytes. For example, if your array list is
initialized as an **int** array list, then the item size will be $`4`$
and the type name will be *"int"*.

Your array list will also be given a starting size value in the
initialization parameters. This value should be used as the starting
maximum size for your array list, which is necessary for allocating the
initial memory block. The default value for the starting size is
$`10`$.

The details of the array list functionality are described in the **Array
Lists** section of this document. The **bool** type referenced in this
contract is found in `<stdbool.h>`. You are expected to do basic
error checking (such as checking for null pointers and correct index
boundaries).

Your **array\_list** program must include the following struct
(typedef-ed appropriately):

| **Structure Name**          | **Fields**   | **Functionality**                                                     |
| :-------------------------- | :----------- | :-------------------------------------------------------------------- |
| \_AList (typedef ArrayList) | void\*\* arr | A pointer to a void pointer. This acts as an array of void pointers.  |
|                             | int size     | The current number of items held by this array list.                  |
|                             | int maxSize  | The maximum number of items this array list can hold before a resize. |
|                             | int itemSize | The size of the data type held by this array list in bytes.           |
|                             | char\* type  | The name of the data type held by this array list as a string.        |

Your **array\_list** program must include the following functions:

| **Requirement**  | **Conditions**                                                                               |
| :--------------- | :------------------------------------------------------------------------------------------- |
| Function         | ArrayList\* alist\_initialize(int, int, char\*)                                              |
| Input Parameters | An integer for setting the starting maximum size, an integer for setting the data type size and a string representing the name of the data type being stored.                            |
| Return Value     | An initialized array list.                                                                   |
| Notes            | An initialized array list will be allocated enough space up to the maximum size, have the data type and item size set appropriately, and will have its current size set to 0. The maximum size should also be stored.                                                          |

| **Requirement**  | **Conditions**                                                                               |
| :--------------- | :--------------------------------------------------------------------------------------- |
| Function         | bool alist\_add(ArrayList\*, void\*)                                                         |
| Input Parameters | A pointer to an array list and a void pointer to an element.                                 |
| Return Value     | True if the element was successfully added to the array list. Otherwise false.               |
| Notes            | This function should insert the given element on the end of the array list.                  |

| **Requirement**  | **Conditions**                                                                               |
| :--------------- | :--------------------------------------------------------------------------------------- |
| Function         | bool alist\_add\_at(ArrayList\*, int, void\*)                                                |
| Input Parameters | A pointer to an array list, an int representing an index, and a void pointer to an element.  |
| Return Value     | True if the element was successfully added to the array list. Otherwise false.               |
| Notes            | This function should insert the given element at the index location in the array list.       |

| **Requirement**  | **Conditions**                                                                               |
| :--------------- | :--------------------------------------------------------------------------------------- |
| Function         | void alist\_clear(ArrayList\*)                                                               |
| Input Parameters | A pointer to an array list.                                                                  |
| Return Value     | None.                                                                                        |
| Notes            | This function should deallocate all array list elements and set the current size to 0.       |

| **Requirement**  | **Conditions**                                                                               |
| :--------------- | :--------------------------------------------------------------------------------------- |
| Function         | void\* alist\_get(ArrayList\*, int)                                                          |
| Input Parameters | A pointer to an array list and an int representing an index.                                 |
| Return Value     | A void pointer to the element stored in the given index of the array list. If the given index is not in the list range, return NULL.                                                 |
| Notes            | This function should return the void pointer stored in the given index of the array.         |

| **Requirement**  | **Conditions**                                                                               |
| :--------------- | :--------------------------------------------------------------------------------------- |
| Function         | int alist\_index\_of(ArrayList\*, void\*)                                                    |
| Input Parameters | A pointer to an array list and a void pointer to an element.                                 |
| Return Value     | The index containing the element. -1 if the element is not in the list.                      |
| Notes            | This function should search the array list for the element and return its index if found.    |

| **Requirement**  | **Conditions**                                                                              |
| :--------------- | :--------------------------------------------------------------------------------------- |
| Function         | void\* alist\_remove(ArrayList\*, int)                                                      |
| Input Parameters | A pointer to an array list and an int representing an index.                                |
| Return Value     | A pointer to the element removed from the list. Otherwise NULL.                             |
| Notes            | This function should remove the element from the list and return it.                        |

| **Requirement**  | **Conditions**                                                                              |
| :--------------- | :--------------------------------------------------------------------------------------- |
| Function         | bool alist\_destroy(ArrayList\*)                                                            |
| Input Parameters | A pointer to an array list.                                                                 |
| Return Value     | True if the array list is successfully deallocated. Otherwise false.                        |
| Notes            | This function should deallocate all of the data, the type name, and finally the array list. |

| **Requirement**  | **Conditions**                                                                              |
| :--------------- | :--------------------------------------------------------------------------------------- |
| Function         | bool \_alist\_resize(ArrayList\*)                                                           |
| Input Parameters | A pointer to an array list.                                                                 |
| Return Value     | True if the array list has been successfully resized. Otherwise false.                      |
| Notes            | This function should attempt to grow the array list by a growth factor of 2.                |

### Postconditions

Your program should be capable of producing and destroying ArrayList
(\_AList) structures. All of the functions should be capable of
executing without crashing. Failure states should be handled by return
values. If a function with a void return type fails, it does not need to
be reported. If you attempt to open a file and the file does not exist
(or the system was unable to create a file pointer), you may exit the
program with an appropriate error. Under normal circumstances, any
functions beginning with an underscore are meant for internal use only,
and will only be called for verification purposes during testing.  
During testing, expect the testing script to iterate through the
underlying array in your ArrayList struct manually in order to verify
its contents and size.

### Restrictions

None.

### File Requirements

This contract requires you to provide a C source file named
`array_list.c` and a C header file named `array_list.h`. Your
header files should contain your forward declarations, struct
definitions and typedefs, as well as any library imports (includes) you
may need. Always protect your header with a define guard. Your source
files must not contain any main functions, or your program will fail
during testing.

In addition to the C files, you will also be required to make a Makefile
for the **array_list** program. Your program will be compiled by
executing **make**. Your Makefile should produce both an
`array_list.o` file and an **array_list** executable file by
compiling your code with the `arrayM.o` file located in
`CI/objects/array_list`.

Your source, header, and make files should be placed in the
`Lab5/array_list/` directory in your GitLab repository.

### Testing

To test your code, you can compile your source files with the
`arrayM.o` object file found in `CI/objects/array_list`. Your
program can then be executed as normal. The object file contains a main
function, so you do not need to provide your own. Using a Makefile for
compiling these files together can save you a lot of time.

### Sample Inputs and Outputs

There are no sample inputs or outputs. The main object file for this
program will test your various functions on an int ArrayList. Your code
should minimally be able to complete the test main function in the
object file, but you may find it more convenient to test your functions
with your own main function first.

## Linked List

### Problem

You must create a structure and set of functions for managing a linked
list.

### Preconditions

You are required to write a program for handling linked lists, which
consists of `linked_list.c`, which should contain all of your
function implementations, and , which should contain your structure
definition, any necessary typedefs, and all of your forward function
declarations. When you compile, you will need to include the source file
in your command in order to ensure the functions exist during the
linking process. You may include any additional helper functions as you
see fit, although they will likely not be necessary. Since you are
dealing with pointers, you will need to check all of your pointers to
ensure they are not null. Trying to perform operations on null will lead
to segmentation faults or other program crashes at run-time.

Your linked list will hold a specific data type (and that data type
only) as defined by the initialization parameters. The size of the data
type held is provided, as is the name. Each element stored in the linked
list should be of the given size in bytes. For example, if your linked
list is initialized as an **int** linked list, then the item size will
be $`4`$ and the type name will be *"int"*.

Your linked list will contain a series of pointers to structs we will
call nodes. Nodes contain the data held at that position of the linked
list, as well as a reference to the previous node and the next node, for
convenience. It is possible for nodes to contain null values for their
pointers when they are on the beginning or end of the node chain of the
linked list, so be careful not to accidentally do any work on null
pointers you don’t intend to.

Whenever a function below inserts or removes data, you will need to
create or destroy any nodes as necessary in order to keep the storage
process hidden. This means that elements will be sent into the function
and you will be required to create a node to contain them, while
ensuring all of the pointers are maintained. Similarly, when data is
removed you will need to destroy nodes and only return pointers to the
data itself. In both cases, it is important to very carefully manage the
state of the pointers, being especially sure to manage your pointers in
the correct order.

Note that the functions below will still use the term "index" to refer
to the $`n`$th element in the list. The linked list should not be
indexed explicitly like an array list, however the index represents the
element which is that many spaces from the front of the list. Thus the
first node is index 0, the second node is index 1, etc.

The details of the linked list functionality are described in the
**Linked Lists** section of this document. The **bool** type referenced
in this contract is found in `<stdbool.h>`. You are expected to do
basic error checking (such as checking for null pointers and correct
index boundaries).

Your **linked\_list** program must include the following struct
(typedef-ed appropriately):

| **Structure Name**           | **Fields**           | **Functionality**                                               |
| :--------------------------- | :------------------- | :-------------------------------------------------------------- |
| \_Node (typedef Node)        | void\* data          | The data held by this node.                                     |
|                              | struct \_Node\* next | The node after the current node in the linked list.             |
|                              | struct \_Node\* prev | The node before the current node in the linked list.            |
| \_LList (typedef LinkedList) | Node\* first         | A pointer to the first node in the list.                        |
|                              | Node\* last          | A pointer to the last node in the list.                         |
|                              | int size             | The current number of nodes (items) held by this linked list.   |
|                              | int itemSize         | The size of the data type held by this linked list in bytes.    |
|                              | char\* type          | The name of the data type held by this linked list as a string. |

You may have noticed that the type of the next and prev pointers in the
Node struct are actually **struct \_Node**. This is to allow the \_Node
structure to contain itself. You won’t be able to easily typedef the
structure before it’s defined, so you have to use **struct \_Node** to
define the pointers. Don’t worry, however. You can still treat them as a
Node (by name) after the typedef is created.  
Your **linked\_list** program must include the following functions:

| **Requirement**  | **Conditions**                                                                           |
| :--------------- | :--------------------------------------------------------------------------------------- |
| Function         | LinkedList\* llist\_initialize(int, char\*)                                              |
| Input Parameters | An integer for setting the data type size and a string representing the name of the data type being stored.                                                                       |
| Return Value     | An initialized linked list.                                                              |
| Notes            | An initialized linked list will have the size, item size, and type set. It will not      |
|                  | have a node attached, so the first and last pointers should be set to NULL.              |

| **Requirement**  | **Conditions**                                                                           |
| :--------------- | :--------------------------------------------------------------------------------------- |
| Function         | bool llist\_add\_at(LinkedList\*, int, void\*)                                           |
| Input Parameters | A pointer to a linked list, an integer index, and a void pointer to an element.          |
| Return Value     | True if the element was successfully added to the linked list at the given index. Otherwise false.                                                                         |
| Notes            | This function should insert the given element at the given index in the linked list.     |

| **Requirement**  | **Conditions**                                                                             |
| :--------------- | :----------------------------------------------------------------------------------------- |
| Function         | bool llist\_add\_first(LinkedList\*, void\*)                                               |
| Input Parameters | A pointer to a linked list and a void pointer to an element.                               |
| Return Value     | True if the element was successfully added to the front of the linked list. Otherwise false.                                                                           |
| Notes            | This function should insert the given element on the front of the linked list.             |

| **Requirement**  | **Conditions**                                                                             |
| :--------------- | :--------------------------------------------------------------------------------------- |
| Function         | bool llist\_add\_last(LinkedList\*, void\*)                                                |
| Input Parameters | A pointer to a linked list and a void pointer to an element.                               |
| Return Value     | True if the element was successfully added to the end of the linked list. Otherwise false.                                                                           |
| Notes            | This function should insert the given element on the end of the linked list.               |

| **Requirement**  | **Conditions**                                                                             |
| :--------------- | :--------------------------------------------------------------------------------------- |
| Function         | void\* llist\_get(LinkedList\*, int)                                                       |
| Input Parameters | A pointer to a linked list and an int representing an index.                               |
| Return Value     | A void pointer to the element stored in the given index of the linked list. If the given index is not in the list range, return NULL.                                               |
| Notes            | This function should return the void pointer stored in the given index of the linked. This should not return a whole Node, but instead the value the node contains as data.      |

| **Requirement**  | **Conditions**                                                                             |
| :--------------- | :--------------------------------------------------------------------------------------- |
| Function         | int llist\_index\_of(LinkedList\*, void\*)                                                 |
| Input Parameters | A pointer to a linked list and a void pointer to an element.                               |
| Return Value     | The index containing the element. -1 if the element is not in the list.                    |
| Notes            | This function should search the linked list for the element and return its index if found. |

| **Requirement**  | **Conditions**                                                                             |
| :--------------- | :--------------------------------------------------------------------------------------- |
| Function         | void\* llist\_remove(LinkedList\*, int)                                                    |
| Input Parameters | A pointer to a linked list and an int representing an index.                               |
| Return Value     | A pointer to the element removed from the list. Otherwise NULL.                            |
| Notes            | This function should remove the element in the given index from the list and return it.    |

| **Requirement**  | **Conditions**                                                                             |
| :--------------- | :--------------------------------------------------------------------------------------- |
| Function         | void\* llist\_remove\_first(LinkedList\*)                                                  |
| Input Parameters | A pointer to a linked list.                                                                |
| Return Value     | A pointer to the element removed from the list. Otherwise NULL.                            |
| Notes            | This function should remove the element from the front of the list and return it.          |

| **Requirement**  | **Conditions**                                                                             |
| :--------------- | :--------------------------------------------------------------------------------------- |
| Function         | void\* llist\_remove\_last(LinkedList\*)                                                   |
| Input Parameters | A pointer to a linked list.                                                                |
| Return Value     | A pointer to the element removed from the list. Otherwise NULL.                            |
| Notes            | This function should remove the element from the list and return it.                       |

| **Requirement**  | **Conditions**                                                                             |
| :--------------- | :--------------------------------------------------------------------------------------- |
| Function         | bool llist\_destroy(LinkedList\*)                                                          |
| Input Parameters | A pointer to a linked list.                                                                |
| Return Value     | True if the linked list is successfully deallocated. Otherwise false.                      |
| Notes            | This function should deallocate all of the nodes, all of the node data, the type name, and finally the linked list.                                                               |

### Postconditions

Your program should be capable of producing and destroying LinkedList
(\_LList) structures. All of the functions should be capable of
executing without crashing. Failure states should be handled by return
values. If a function with a void return type fails, it does not need to
be reported. If you attempt to open a file and the file does not exist
(or the system was unable to create a file pointer), you may exit the
program with an appropriate error.

During testing, expect the testing script to iterate through the
underlying nodes in your LinkedList struct manually in order to verify
their contents and size.

### Restrictions

None.

### File Requirements

This contract requires you to provide a C source file named
`linked_list.c` and a C header file named `linked_list.h`. Your
header files should contain your forward declarations, struct
definitions and typedefs, as well as any library imports (includes) you
may need. Always protect your header with a define guard. Your source
files must not contain any main functions, or your program will fail
during testing.

In addition to the C files, you will also be required to make a Makefile
for the **linked\_list** program. Your program will be compiled by
executing **make**. Your Makefile should produce both a
`linked_list.o` file and a **linked\_list** executable file by
compiling your code with the `linkedM.o` file located in
`CI/objects/linked_list`.

Your source, header, and make files should be placed in the
`Lab5/linked_list/` directory in your GitLab repository.

### Testing

To test your code, you can compile your source files with the
`linkedM.o` object file found in `CI/objects/linked_list`. Your
program can then be executed as normal. The object file contains a main
function, so you do not need to provide your own. Using a Makefile for
compiling these files together can save you a lot of time.

### Sample Inputs and Outputs

There are no sample inputs or outputs. The main object file for this
program will test your various functions on an int LinkedList. Your code
should minimally be able to complete the test main function in the
object file, but you may find it more convenient to test your functions
with your own main function first.

# Submission

## Required Files

When submitting this lab, you must submit your C source and header files
only. Each file must be contained in the directory listed in the
structure requirement diagram below. These files include:

1.  `array_list.c`
2.  `array_list.h`
3.  `linked_list.c`
4.  `linked_list.h`
5.  `Makefile` (for array\_list)
6.  `Makefile` (for linked\_list)

As with all labs, submitting anything other than what is required in
this section will cause the testing pipeline to fail.

## Submission Procedure and Expectations

Your code will be submitted to your Lab 5 GitLab repository using the
same method as outlined in the Lab Technical Document. Refer to that
document if you do not remember how to submit files via the GitLab
service. A link to your repository can be found in the `Lab5` subgroup
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
submission. **Do not rely on us to perfectly test your code.** The CI/CD
pipeline is a great tool for helping you debug major parts of your
submissions, but you are still expected to follow all rules as they have
been laid out.

## Submission Structure

In order for a submission to be considered valid, and thus testable,
your git repository must contain directories and files in the following
structure:  

```plaintext
Lab5/
 ┣ array_list/
 ┃  ┣ array_list.c
 ┃  ┣ array_list.h
 ┃  ┗ Makefile
 ┗ linked_list/
    ┣ linked_list.c
    ┣ linked_list.h
    ┗ Makefile
```

As with all labs, accuracy is incredibly important. When submitting any
code for labs in this class, you *must* adhere to the directory
structure and naming requirements in the above diagram. Failure to do so
will cause the testing pipeline to fail.

Remember to remove `Lab5/delete_this_file` from your repository
using <kbd>git rm</kbd> to avoid any pipeline failures.
