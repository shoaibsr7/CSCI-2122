# Introduction

This lab is designed to introduce you to command line arguments, reading
and writing files, the wonderful world of memory management, and
structures. By the end of this lab, you will be expected to understand
the following:

1.  Reading arguments from the command line.
2.  Pointers.
3.  File I/O.
4.  Memory management.
5.  Type definitions (typedef).
6.  Structures (struct).

The proceeding labs will build and expand this knowledge into the realm
of low level computing, including memory management, data structures,
methods for approaching low-level computation, and a variety of other
subjects. As such, knowing these key principles will be important for
future programming and development.

In this lab you are expected to perform the basics of cloning your Lab 4
repository from the GitLab course group. A link to the course group can
be found
[<span style="color: blue">here</span>](https://git.cs.dal.ca/courses/2022-fall/csci-2122)
and your repository can be found in the Lab4 subgroup. See the Lab
Technical Document for more information on using git. You will notice
that your repository has a file in the `Lab4` directory named
`delete_this_file`. Due to the limitations of GitLab, we are not
able to push completely empty directories. Before your push your work to
your repository (which should be in the `Lab4` directory anyway), make
sure to first use the <kbd>git rm</kbd> command to remove the extra file. If
you do not, your pipeline will fail.

**Be sure to read this entire document before starting!**

# Table of Contents
[[_TOC_]]


# Pointers

In C, the only way to transfer data between functions is to pass a copy
of the desired values, which happens automatically. For example, if you
want to take an integer value and push it into a function via the
function arguments, C will allocate a new memory block for that integer,
initialize it to the same value as the value being passed, then provide
the function with the newly allocated variable instead of this original.
The same thing occurs when you assign a variable holding a primitive
data type to a new variable of the same type. Consider the following
example:

``` c
int a = 13;
int b = a;
b = b + 5;
int c = a + b;
```

After that code is executed, what is the c variable’s value? Common C
logic would dictate that $`c = 13 + 13 + 5 = 31`$, but if C did not
create copies of primitive values, something different would happen:
$`a = 13`$, then $`b = a`$, but because we aren’t creating copies, $`b`$
becomes $`a`$ by being assigned $`a`$’s *memory location*. This means
that both $`b`$ and $`a`$ are now using the same place in memory to
store their value, so anything that happens to $`a`$ will also happen to
$`b`$. Next, $`b = b + 5`$, which means $`b = 18`$, but since $`a`$ also
uses $`b`$’s memory location, $`a = 18`$ now as well. When
$`c = a + b`$, let’s assume the arithmetic add produces a brand new
value (because if it didn’t, this would really be a brutal pain to deal
with), and since $`a`$ *is* $`b`$, this means $`c = 18 + 18 = 36`$, a
far cry different from our normal expectations.

As such, it’s important that C (and basically every other language)
adheres to some form of pass-by-copy in order to function properly.
However, there will be times when it’s beneficial to not pass-by-copy in
the traditional sense, but instead pass a copy of a piece of data’s
*memory address*. Having the ability to do this introduces several
benefits:

1.  We are able to pass large blocks of data between functions without wasting time copying that data in its entirety.
2.  We can work directly on a single piece of data by using a variety of functions, rather than one long function.
3.  We can control the way data is conceptualized by the system by manipulating the way C is viewing that data.

At its most basic level, a pointer is a variable that holds a memory
address. Every time a variable is created, a space in memory is held by
the system which is equal to the size of the variable’s data type. For a
regular variable, it’s possible to access that memory location by using
the <kbd>&</kbd> operator, also known as the **address-of** operator. You may
have noticed that it is necessary to use the <kbd>&</kbd> operator when scanning
input. This is to ensure that we don’t make a new copy of a variable’s
memory space, and instead completely replace the value in the variable’s
memory space. If you have access to a variable’s memory address, you are
able to alter the contents of that variable in-place, circumventing the
normal pass-by-copy rules:  

``` c
#include <stdio.h>

int main(int argc, char** argv)
{
    // Assign a = 13.
    int a = 13;
    
    // Create a pointer b and set it to a's memory address.
    int *b = &a;
    
    // Change the value held at b's memory address to 25.
    *b = 25;
    
    // Assign c to the value stored in b's memory address.
    int c = *b;
    
    // Add 15 to c.
    c = c + 15;

    // Print all of the variables' values.
    printf("%d, %d, %d\n", a, *b, c);

    // Return a successful exit code 0.
    return 0;
}
```

You may notice that the $`b`$ variable is written differently than what
you’re normally used to. When you initialize a variable, you can place
an asterisk **\***, which we normally call star for short) in front of the
variable name to designate it as a **pointer** to a memory address.
These asterisks can be "stacked", creating pointers to pointers, which
comes up frequently with arrays. Since a string is technically an array
of characters, it can be represented by a **char \***. If you want an
array of strings, you need a pointer to a string, which means an array
of strings can be represented by **char \*\***, with the first pointer
star referring to an array, and the second start referring to the string
contents, effectively giving you an array of arrays, where each inner
array element is of type char. You may notice that sometimes the stars
are placed on the data type instead. Both are acceptable formats, but if
you plan on initializing several variables on the same line, you will
need to specifically designate each variable as a pointer, as
necessary.

When you create a pointer, you are effectively pointing at a "box" in
memory (a memory address) containing the relevant data. In order to
access that data, you need to **dereference** the pointer. If you are
currently working with a pointer variable, putting a star in front of it
will tell C to use the value being pointed at. In the above example, a
pointer $`b`$ is created on line $`9`$, which points to the memory
address of $`a`$. On line $`12`$, we tell our program to deference $`b`$
and change the value in that memory location to $`25`$. Because $`b`$ is
pointing to $`a`$’s memory address, we are altering $`a`$’s value. On
line $`15`$, we assign a value to $`c`$. That value is the one stored in
$`b`$’s memory address, which is the value of $`a`$. Since that value is
not a memory address and is instead a primitive data type, we make a
copy of that value (which is $`25`$) and store it in $`c`$. When we
print the values on line $`21`$, you will see the final values of each
variable.

One thing to consider which is very important is memory addresses are
sized (as a general rule) based on the bit-size of the computer system.
That means if you have a 64-bit system, as most modern computers today
are, then the system is able to contain roughly $`2^{64}`$ memory
addresses, where each memory address is 1 byte. Some simple math would
suggest a system could therefore hold about 18 billion gigabytes of
memory. No system is currently capable of holding that much RAM, and
some system limitations could apply which would reduce that number, but
it may only be by small factors. In order for us to be able to represent
that many memory locations, we need a large integer data type, otherwise
we wouldn’t be able to access all of the memory in our system
(someday).

Timberlea is a 64-bit Debian system and represents memory addresses with
**unsigned long** values. This means memory addresses can never be
negative, can hold up to a maximum integer value of $`2^{64}-1`$, and
understanding that a memory address is simply a very large integer value
"under the hood" means you can abstract memory in your mind as a very
large array of bytes and a pointer is an unsigned long which holds an
index to that array. Whenever you are using a pointer, it’s pointing to
a specific memory array index so it knows where to find your data.  
As with all variables, when you create a pointer it is good practice to
assign it an initial value, to ensure you are not working with any
artifacts of previous memory state. The default value for pointers is
**NULL**, and your pointers should either be set to NULL or a memory
space immediately to avoid any strange memory issues. One of the worst
errors you will run into in C is called a **Segmentation Fault**, which
is telling you that you have tried to access a memory location your
current program does not yet own. This could mean that you failed to
create a memory block for a pointer to point to, or that you tried to
write outside of the bounds of a memory space you own. Segmentation
Faults can be very challenging to debug, as they offer no indication of
their timing or program location. Later in the course we will
investigate tools for helping you debug run-time errors, but for now
you’ll likely just have to start tracing with print statements! The
best advice we can give you is that whenever you create a pointer, make
sure you store a value in it. It’s possible for pointers to start by
pointing to "nothing" (which is to say, they may point at nothing, or
actually somewhere random), which can cause memory problems later.
Always initialize your pointers to something, even if it’s null!

The following program declares an array of integers, then assigns its
address to a pointer variable. Depending on how you create them, arrays
can appear to function strangely as far as pointers are concerned, but
ultimately all arrays are managed by a pointer variable. Try executing
the following code to see how C manages the functionality of the integer
array.  

``` c
#include <stdio.h>

int main(int argc, char** argv)
{
    int arr[] = {7, 16, 51, 72, 103};
    int *arrPtr = arr;
    long diff = (long) &arrPtr[1] - (long) arrPtr;

    printf("Address of arr[0]  = %x\n", arrPtr);
    printf("Address of arr[1]  = %x\n", &arrPtr[1]);
    printf("Long Difference    = %ld\n", diff);
    printf("Address Difference = %ld\n", &arrPtr[1] - arrPtr);
    printf("Value of arr[0]    = %d\n", *arrPtr);

    return 0;
}
```

We do a few things in here that you may not have seen before. We create
an integer array in the way you’re used to seeing, using an array
literal with **{ }**. We then create a pointer to an integer and store the
array in it directly. It turns out that arrays are simply blocks of
memory and a pointer is always assumed to be pointing to the first
indexed location in the array, which is equivalent to arr\[0\].

Next, we take the memory address of the second element of the array,
then subtract from that the memory address of the first element. Notice
that we have to convert those to longs in order to achieve the proper
result. We can then print a variety of information about the array. If
you run this code, you may notice something strange. The value we stored
in diff is different from the value we get when we subtract the
addresses normally. Why is this?

## Pointer Arithmetic

Because memory addresses are just numeric values, you can perform
arithmetic operations on pointers. The pointer arithmetic operations are
$`+, -, ++, --`$. When you increase a pointer’s value by 1, you
are actually increasing its value by **one data type bit length**, where
an increase of 1 technically covers 1 byte of memory. The smallest
allocatable unit in most computer systems is 1 byte, which means every
change of 1 in your pointer value equates to pointing to the next byte
in memory.

This means that if you have a block of memory currently assigned to an
integer pointer, incrementing that pointer’s value will actually
increment it by 4, because integer data on Timberlea takes up 4 bytes.
This is why the differences in the previous example program were
different: from the point of view of regular arithmetic (stored in the
diff variable), the difference in the memory addresses between two
adjacent values in an array is equal to the number of bytes in the data
type the array is storing, in this case an int. Since the int data type
is 4 bytes wide, the difference between the adjacent indexed elements is
**4 bytes of memory**. However, from the point of view of pointer
arithmetic, these locations are a single data type step apart, and thus
the memory address distance (without converting the addresses to a
integral type) is **1**, or **1 int width**.

In the following piece of code, you can see how the pointer increment
will iterate through the array in a similar way to using the arr\[i\]
method. Try changing the data type/values of the array and checking the
size of the memory address on every step to get an idea of how pointer
arithmetic works with different data types.  

``` c
#include <stdio.h>

int main(int argc, char** argv) 
{
    int  arr[] = {7, 16, 51, 72, 103};
    int *arrPtr = arr;
   
    for(int i=0; i < 3; i++) 
    {
       printf("Address of arr[%d] = %x\n", i, arrPtr );
       printf("Value of arr[%d] = %d\n", i, *arrPtr );
       arrPtr++;
    }
    
    return 0;
}
```

## Passing Pointers to Functions

As we mentioned previously, C is always pass-by-copy. In the case of
pointers, it’s still pass-by-copy (not to be confused with
pass-by-reference), where C interprets the value being copied as a
pointer, based on the parameter signature of the function in question.  
You may have noticed that when we pass strings or arrays to functions,
we can receive them or send them in a variety of different ways. Since a
string is a character array, they can be represented as <kbd>char str[]</kbd>
or <kbd>char *str</kbd>. Arrays are also represented in this way, although
both strings and arrays using the pointer format (type \*) will need to
ensure they are allocated memory before being worked with (see the
Memory Management section below).

Since you are accepting a memory address of an existing value, any
changes made to that value will be reflected outside of the function.
This is why when you pass a string into the **strrev(char\*)** function
you wrote in Lab 3, you didn’t have to return the string when you were
done. Be very careful about how you use pointers, as you may be
overwriting things you don’t intend to. Consider the following example
code:  

``` c
#include <stdio.h>

void change(int *a)
{
    a[5] = 15;
}

int main(int argc, char** argv)
{
    int a[15] = {0};

    for(int i=0; i < 15; i++)
        printf("%d ", a[i]);
    printf("\n");

    change(a);

    for(int i=0; i < 15; i++)
        printf("%d ", a[i]);
    printf("\n");

    return 0;
}
```

We start by creating an array $`a`$ with a capacity of 15 and initialize
all of its elements to 0. We then print every element in $`a`$. We then
call the change(int \*) function on $`a`$, which changes its 6th value
to $`15`$. Without returning that array, we simply print the array again
and note the differences. In this example you can see that the pointer
being passed in gave us the ability to modify the original array
directly. Since C does not have objects and does not have methods (which
are generally class functions), we will need to write functions which
accept pointers to data so that we can modify it in a similar way to
object-oriented approaches. That is, rather than writing a LinkedList
class and that class having a **void addFirst(T element)** method which
is accessible on each instantiation of LinkedList, you will need to
create a structure which can be initialized to represent a LinkedList,
then pass it into a function using a pointer, such as **void
addFirst(LinkedList\*, void\* element)**.

Remember that a pointer is just an **unsigned long**. This means that
when you pass it into a function, the function is simply making a copy
of that **unsigned long** value. Once the function has a copy of that
value, it will be the same memory index value as the one the calling
code contained. This means it still points to the same memory index and
any changes you make to that memory index are reflected everywhere in
your program.

## Arrays vs. Pointers

Up until this point, we’ve been referring to arrays and pointers as
equivalent, but the the truth is that there are some subtle (but
important) differences between them.

In a practical sense (as in, the way you will use them), arrays and
pointers are basically the same thing. An array is a block of memory
with a fixed size which is equivalent to the size of the data type held
in it multiplied by the number of things it’s capable of holding. Memory
can be allocated to meet the same requirements, and it turns out that
you can use array notation to iterate through a block of memory being
held by a pointer. You may recall that when an array is created, the
array’s first memory address is held in the variable, which is the same
for memory addresses held by pointers. If you have a memory block that’s
large enough to hold 10 integers and you want the 5th integer,
**pointer\[4\]** will get it the same way that **array\[4\]** can get it
from an array capable of holding 10 integers. So how are they different?

### Arrays Are Fixed Size and Live Forever

An array is a specific type of data in C, and is initialized as such.
While they are allocated memory, C handles that allocation for you. This
means that once an array is created, it can’t be "uncreated" except by
ending your program, and it cannot be resized. Once you make an array,
it will live until your program ends.

To contrast this, memory blocks that you allocate using **malloc** or
**calloc** (see Memory Management below) can be resized using the
**realloc** function, or released back to the operating system using the
**free** function. This means you have more direct control over your
memory allocations and how they affect your system.

### Arrays Know How Big They Are

Because arrays are a data structure that C controls, using the
**sizeof** statement on an array will return the total size of the array
in bytes. Because of this feature, you can technically find the length
of an array by finding the size of the array and dividing it by the size
of one of the elements in the array. If you do this, the number you
produce will be the maximum storage capacity of the array.

Memory blocks are allocated by the user and the length of those block is
not recorded in a place accessible by the user, so it’s important that
you record the length of your memory blocks whenever you might need
them. Using the **sizeof** statement on a pointer will always return the
size of a memory address, which is an unsigned long integer on
Timberlea. This means the size of all pointers is 8 bytes, which also
means you cannot use the same trick for sizing arrays in order to figure
out the length of a memory block.

### Arrays Can Be Stored in Pointers

It’s possible to store an array in a pointer, since an array is already
being stored as a memory address. If you convert an array to a pointer,
then you should always be aware that it will lose the standard array
functionality. After all, if an array’s memory address is now being
treated as a pointer, C only knows how to do "pointer things" to
pointers, and thus you will lose the ability to get the size of the full
memory block as long as the array is stored in the pointer.

## Function Pointers

Function pointers are a special type of pointer which allow you to
dynamically reference and call functions. They will take some practice
to really understand, and they break a few of the regular formatting
rules, which we can see below.

A function pointer is structured as follows:  

``` c
returnType (*pointer_name)(paramType1, paramType2, ..., paramTypeN) = function_name;
```

Thus, if you wanted to create a pointer to a function **add** and call
it, you might do it as follows:  

``` c
#include <stdio.h>

double add(double a, double b)
{
    return a + b;
}

int main(int argc, char** argv)
{
    double (*myAdd)(double, double) = add;
    
    printf("Add Result: %lf\n", myAdd(1.5, 3.0));
    
    return 0;
}
```

This means storing a function pointer is a modified way of storing any
other variable. The return type of the function is the variable's type,
the variable name is formatted like a pointer (in brackets), and the
function's parameter signature is attached to the variable name. As long
as the function you want to store matches this format, you can simply
assign it by name.


In the above example, if you want to instead pass that function into
another function to be executed:


``` c
#include <stdio.h>

double add(double a, double b)
{
    return a + b;
}

void printResult(double (*thatAdd)(double, double))
{
    printf("Add Result: %lf\n", thatAdd(1.5, 3.0));
}

int main(int argc, char** argv)
{
    double (*myAdd)(double, double) = add;
    
    printResult(myAdd);
    
    return 0;
}
```

If for some crazy reason you might need to create an array of these
functions, you may want to throw another star on the front of the
pointer name and create an array using array literals.

# File I/O

Being able to write to and from files is similar to other languages, and
thus we won’t go into excessive detail here. As far as good practice is
concerned, it follows the same pattern as most other languages:  

1.  Create a pointer to file using a file open function and set your file mode (read, write, append, etc.)
2.  Ensure the file exists by verifying the file pointer exists.
3.  Either read from or write to the file using the appropriate file manipulation functions.
4.  Release the file from the program by using a close statement.

In C, all of the file I/O functionality is found in the stdio.h library,
as well as a few useful additions from the POSIX libraries available on
Timberlea. Most POSIX functions have been ported over to other compilers
over the years, but we will still provide no warranty on systems outside
of Timberlea.

The FILE data type is a specific pointer type held by the standard I/O
library. It is used to hold an open file pointer and is interacted with
directly by the various file-manipulation functions.

To open a file, you will use the **fopen(char \*filename, char \*mode)**
function, where the **filename** string is a path to the file and the
**mode** string is a set of characters representing the mode you want
the file to be opened in, where the basic values can be **"r"** (for
reading only), **"w"** (for writing only), and **"a"** (for appending
only). There are compound reading/writing modes, as well as binary
reading/writing modes available in C.

In order to read from a file (or any stream of your choosing), you may
use the following functions:

1.  **fscanf:** Works similarly to scanf, except you provide it a specific stream to read from. This can be used with most the standard streams as well as file streams. Both scanf and fscanf have a return value equal to the number of items they read during their execution, which can be used to determine whether or not you’ve reached the end of a file. Not recommended for the same reason scanf is not recommended (conflicts with buffer sizes and undefined behaviour).
2.  **fgets**: Works similarly to gets, except you provide it a specific stream to read from. This is a good option for avoiding buffer conflicts, as you must set a specific buffer size *n*, stopping it from overflowing your buffers. This is the best option for meeting the C standard.

3.  **getline**: This function is POSIX-supported (as well as in many other compilers), but is not C standard. You may need to include a **#define _GNU_SOURCE** at the top of your code (before you include **stdio.h**) in order for this to be properly loaded. It’s a very useful function which reads an entire line (any number of characters, up to a newline symbol) and will ensure that the buffer/string you provide it is properly sized to handle the incoming data. This is probably the cleanest way to read a line if you don’t know how long the line will be.

Writing to a file should be done using **fputs**, which accepts a string
buffer and a file pointer/steam, then writes that buffer to the file.
Whenever you’re done working with a file, you should always use
**fclose(filePointer)** to ensure the file is released from the program
and not left stuck in use. This is also important for forcing any
remaining write buffer to be applied to the file. If you don’t want to
close a file, but want the buffer to be forced to write, you can also
use **fflush(filePointer)**. This method can also be used on stdout, if
your buffered print statements are not being applied.  

An example of reading from a file and writing to a file can be seen
here:

``` c
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
    char *buffer = malloc(sizeof (char) * 30);
    FILE *filePointer = fopen("whoa", "w");

    fputs("be excellent to each other\n", filePointer);
    fputs("and party on, dudes\n", filePointer);

    fclose(filePointer);

    filePointer = fopen("whoa", "r");

    fgets(buffer, 30, filePointer);
    printf("%s", buffer);
    fgets(buffer, 30, filePointer);
    printf("%s", buffer);

    fclose(filePointer);
    free(buffer);

    return 0;
}
```

## fflush

The **fflush** function from the stdio.h library is very useful for
debugging. It is a function which accepts a pointer to a file stream as
its only parameter. When the function executes, it checks if the buffer
is waiting to write data stored inside it and if it is, it forces that
information to be written to the correct location. This is useful for
when you want to ensure you’ve written everything to a file before
continuing, but is also useful for debugging situations.

By default, most operating systems are opportunistic about when they
write buffers to file locations. This is true for files, because writing
to the hard drive is very slow, but is also true for writing to the
terminal. You may find that your print statements are sometimes not
being printed to the screen when an error occurs, such as a segmentation
fault. This is because the system was waiting for the **stdout** buffer
to fill before printing everything in it to the screen, which is a good
policy for limiting the number of times printing has to happen (thus
saving CPU cycles). However, if you get a segmentation fault, your
program ends and the buffer is discarded, leaving you with no output to
your screen and making error checking harder to perform. If you find
yourself in this situation, using **fflush(stdout)** after your key
print statements will ensure they’re printed to the screen immediately,
so you can get any necessary debugging feedback before your programs
crash.

# Memory Management

In the previous program, you probably noticed that we used a function
called malloc and assigned its value to our buffer. This function
provides us with the ability to create a block of memory based on the
size argument we give it. Being able to assign memory goes hand-in-hand
with pointers and gives you better control over what your code is
doing.

By default, if you create any data type without initializing it as a
pointer, the C compiler will take it upon itself to allocate memory for
you. However, this creates an issue where every array you make is left
in memory for the entirety of your program. C does not have any form of
garbage collection when it comes to memory management, so your memory
can generally only be in a C-controlled state or a programmer-controlled
state.

For example, when you create an array using the array literal and an int
arr\[\] variable definition, C will allocate that memory and not let you
touch it. If you make many arrays this way, you can quickly create a lot
of unnecessary memory usage, as those arrays are not able to be
deallocated by you. However, if you instead use an integer pointer and
allocate memory manually using a function like malloc, C will give you
the opportunity to release that memory back to the operating system,
meaning your programs can run at much lighter weight. That said, the
drawback is that you now have to remember to release all of your memory
every time you make it, and some programmers have a hard time keeping
track of all the memory they’ve allocated. Try not to create too many
memory leaks by taking full advantage of the memory allocation tools
while also remembering to free any memory you’re no longer using.

In this section, you may find references to the **size\_t** and
**ssize\_t** types. These are type definitions provided by the C
standard and, on Timberlea, are effectively interchangeable with
**unsigned long** and **long** respectively. In fact, using the
appropriate long in place of the size types is fairly common. However,
as usual, not using the size types can potentially lead to undefined
behaviour. If you have trouble, don’t say we didn’t warn you.

## malloc

The malloc(size\_t size) function will allocate the requested amount of
memory (given by size\_t size) in bytes and return a pointer to the
memory address at the beginning of the block it allocated. The pointer
returned by malloc is of type void, which you may see people casting to
other pointer types. This is unnecessary (as void \* always
automatically casts with priority to the pointer type it is being
assigned to) and can actually lead to trouble by hiding bad memory
allocations behind an explicit cast, which could produce errors later
when you least expect them. This is caused by multiple versions of the
malloc function existing in C and you don’t want to use the wrong one.

:exclamation: :boom: $`\textcolor{red}{\text{Never cast malloc’s return value to anything, ever! You will see people do it, but you shouldn’t do it.}}`$

$`\textcolor{red}{\text{Just don’t do it.}}`$

$`\textcolor{red}{\text{Don’t.}}`$ 

$`\textcolor{red}{\text{Stop.}}`$

$`\textcolor{red}{\text{Please.}}`$ 

(This rule does not apply to C++, where you have
to cast it. Go figure.)  


``` c
ptr = malloc(sizeInBytes);
```

malloc is often used in conjunction with the **sizeof** statement, to
indicate how many bytes to allocate for a given data type. The sizeof
statement is a built-in C statement which will return the total size
required to store a particular data type. This even works on structs and
custom type definitions. Contrary to popular belief, sizeof is not a
function and does not explicitly require parentheses to operate.
However, depending on how you structure your size equation, it may be
necessary to surround the type with parentheses to avoid conflicting
operators.

For example, to allocate enough space to hold 15 floats:  

``` c
float *floatPointer = malloc(15 * sizeof(float));
```

One thing to always remember about malloc is that, by the C standard, it
will not alter the memory before returning a pointer to it. This means
that the memory it allocates could contain remnants of previously used
and discarded data, which you should be sure to initialize into
something meaninful, even if it’s 0’s. You may find the version of gcc
on Timberlea does not necessarily adhere to the C standard, but it’s
worth knowing for other systems.

## calloc

The calloc function is almost identical to malloc, except calloc will
set all of the bits in the allocated memory to 0 before it returns a
pointer to that memory. It also explicitly takes the size of the data
type and the number you want to allocate separately as
**calloc(numberToMake, size)**. This used to be referred to as the
"array allocation" function.

## realloc

The realloc function will resize the amount of memory a pointer points
to; either increasing or decreasing it. realloc will even move to a
larger block of memory, if it has to. This is very useful for things
increasing the size of an array, for example. realloc takes a pointer
and a size as arguments, and returns a pointer to the resized memory
location. This may not be the same pointer you started with, so make
sure you store it properly. If ralloc fails, it returns NULL, so always
save its return value to a new pointer. If you don’t, you may
accidentally overwrite your original, unmodified pointer when realloc
fails, as it only frees your original pointer if it was able to allocate
new memory.

## free

Memory that is manually allocated must be manually released back to the
operating system. This tells the computer that you are done using the
memory so it can be used for some other purpose. Memory you allocate
manually will be released when your program ends, but as long as your
program is running, any memory you have allocated will stay allocated,
which can lead to memory leaks and potential system instability if you
allocate enough of it. You should always use the free function to
release memory you’re no longer using, as soon as you’re done with it.

The free function takes one argument: the pointer to the memory you want
to deallocate. Don’t use free until you’re sure that you’re done using
the data you’re about to free, as operating systems tend to be very
immediate when choosing a memory location to allocate to you. Once the
memory is gone, it’s very unlikely you will get the exact same block of
memory back in the same place.  

``` c
// Create an array which can hold 15 floats.
float *floatPointer = malloc(15 * sizeof(float));

// Allocate enough memory for 9 chars. Since malloc's size
// units are in bytes, we don't need to use sizeof.
char *charPointer = malloc(9);

// Free the memory that was allocated.
free(floatPointer);
free(charPointer);

// Set those pointers to null to avoid dangling pointers.
floatPointer = NULL;
charPointer  = NULL;
```

To avoid any **dangling pointers**, which are pointers that were
referencing some memory which has been deallocated, make sure that when
you free a pointer you set it to a new value afterward, even if that
value is NULL.

# Structures

Structures in C are something of a precursor to classes in object
oriented languages. They are a means of grouping data together into a
block of memory which is field-accessible, mutable, and easy to
initialize. If arrays are data structures which hold a group of values
of the same data type, a structure can be seen as a data structure which
holds values of different data types.

## struct

A struct is a user-defined data type that allows you to combine data of
different types into a single collection. Structs are useful for record
keeping tasks. For example, if you wanted to keep information about a
pet, you might want to record the pet’s name, species, age, weight, and
owner’s name.

You can define a struct with the struct statement, which is a compound
statement combining the struct keyword with a struct tag. Any time you
want to reference that specific struct type again, it is not enough to
simply name the struct’s tag, as you will see below. The definition for
a struct is followed by a code block containing a series of fields (also
called members) which define the struct’s content.

Consider the following application of structs for a pet owner’s records:

``` c
struct _Pet 
{
    char name[100];
    char species[100];
    int age;
    int weight;
    char owner[100];
};
```

This struct is named \_Pet, and contains strings and integers which
define the features of a pet that its owner has deemed important. Any
time this struct is created, these fields will be created inside its
memory block for use by the programmer. Accessing a field in the struct
varies based on whether or not it is a struct, or a pointer to a struct.
Accessing a field uses dot notation (structVar.fieldName) when you are
accessing the struct directly, or arrow notation
(structPointer->fieldName) when accessing a struct through a
pointer.

## typedef

The typedef keyword lets you assign an alias to an already existing data
type. While this can be used on any C data types (including primitive
types), you will likely see it used most often with structs. Since you
would normally have to repeatedly use the struct keyword and tag
together to reference a specific struct type, using the typedef function
can make it simpler to access your structs and help shorten your code
while increasing readability.  
The following example shows how to assign an alias to the int data type:

``` c
#include <stdio.h>
typedef int integer;

int main(int argc, char** argv)
{
    integer i = 12;
    printf("%d", i);
    
    return 0;
}
```

In the pet example, it would be useful to not have to write **struct
\_Pet** every time we want to use the struct. To get around this, we can
simply typedef the struct type to be a single identifier. In our case,
we want to specifically keep records on dogs, so we can turn the \_Pet
struct into a Dog type. Notice that our struct typedef identifiers are
all starting with a capital letter. This is fairly common practice and
serves to help you quickly identify when a type is a struct. The typedef
is executed here to create the Dog type, which is then used to create
two different Dogs and print their records:  

``` c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _Pet
{
    char name[100];
    char species[100];
    int age;
    int weight;
    char owner[100];
} Dog;

int main()
{
    // Automatic struct memory allocation.
    Dog goodBoy;

    // Manual struct memory allocation.
    Dog *badBoy = malloc(sizeof(Dog));

    // Initializing values for the good boy.
    strcpy(goodBoy.name, "Waffle");
    strcpy(goodBoy.species, "Border Collie");
    goodBoy.age = 4;
    goodBoy.weight = 40;
    strcpy(goodBoy.owner, "Robert Smith");

    // Initializing values for the bad boy.
    strcpy(badBoy->name, "Jasper");
    strcpy(badBoy->species, "Pug");
    badBoy->age = 12;
    badBoy->weight = 119;
    strcpy(badBoy->owner, "Caleidgh Bayer");

    // Print the Good Boy's information.
    printf("Dog name: %s\n", goodBoy.name);
    printf("Dog species: %s\n", goodBoy.species);
    printf("Dog age: %d\n", goodBoy.age);
    printf("Dog weight: %d\n", goodBoy.weight);
    printf("Dog owner: %s\n\n", goodBoy.owner);

    // Print the Bad Boy's information.
    printf("Dog name: %s\n", badBoy->name);
    printf("Dog species: %s\n", badBoy->species);
    printf("Dog age: %d\n", badBoy->age);
    printf("Dog weight: %d\n", badBoy->weight);
    printf("Dog owner: %s\n\n", badBoy->owner);

    return 0;
}
```

# Command Line Arguments

Like any program, C programs are able to accept command line arguments
from the operating system in the form of an array of strings. This
allows a user to provide starting information to a program, which is
useful in a number of ways: it allows regular program behaviour to be
modified with a series of arguments which are not specifically provided
via stdin, meaning data can be piped into the program while still being
able to modify its functionality; it also allows programs to be run via
script without the explicit need of parameter files and other external
controls.

So far in this course we have been referring to the various command-line
strings as **commands** (and will continue to do so), but it’s worth
recognizing that they’re actually C programs which accept a series of
string arguments, which are provided by the operating system during
execution.

When you write your main function, you may have noticed that we have
been structuring it in a very specific format:

``` c
int main(int argc, char** argv) 
{
    return 0;
}
```

The arguments that the main function take in its function definition are
**argc** and **argv**, which stand for **ARGument Count** and **ARGument
Values**. The argument values are an array of strings which represent
the individual string tokens provided by the user after they selected
which program to run, and the argument count is an integer which is
equal to the length of the argument values array. If you were ever
wondering what the various options meant for things such as **ls**, this
is how it is done!

The argv array contains the entire tokenized command that was used to
execute the program or command. This array is held in memory by the
operating system and referenced by the system so that it knows what has
been executed. It then passes that array into the main function. The
first element of the argv array is the name of the program. Starting at
argv\[1\], you will receive each subequent command line argument. Using
the example of ls, if you enter the command **ls -a -l** into the Unix
terminal, you are executing a C program called **ls**, which receives
the following arguments in its argv array and argc values:

argv\[0\] = "ls"

argv\[1\] = "-a"

argv\[2\] = "-l"

argc = 3

Since you have the ability to manipulate and use those values as you see
fit, they’re a great way of accepting configuration information from
users without requiring them to move through menu selections.  

# Lab 4 Function Contracts

In this lab you will be responsible for fulfilling two lab contracts:
the **book** contract and the **calculator** contract. Each contract is
designed to test you on some of the things you’ve learned throughout the
instruction portion of this lab.

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
additional libraries, as they should not be required.

For those of you who are concerned, when deciding which naming
conventions you want to use in your code, favour consistency in style,
not dedication to a style that doesn’t work.  

## Book

### Problem

The month of October has begun and you want to read some classic horror
stories as you get closer to Halloween. Unfortunately, the thought of
seeing certain words in text form is frightening to you! You must write
a Book library which reads in a book from a text file and removes any
lines which contain a specific word.

### Preconditions

You will have access to the classic horror short stories *I Have No
Mouth, And I Must Scream* by Harlan Ellison and *The Shadow over
Innsmouth* by H. P. Lovecraft in ASCII text files (***consider this your
content warning if you decide to read them***). You will create a struct
for holding the simple contents of a book and provide a series of
functions for initializing, manipulating, and destroying said books.

Your `book.h` header file will contain forward definitions, struct
definitions and typedefs, and any necessary library imports to ensure
the proper operation of your functions. You must also write an
accompanying `book.c` file containing all of the matching function
implementations. When you compile, you will need to include the source
file in your command in order to ensure the functions exist during the
linking process. You may include any additional helper functions as you
see fit, although they will likely not be necessary. Since you are
dealing with pointers, you will need to check all of your pointers to
ensure they are not null when they are passed into your functions.
Trying to perform operations on null pointers will lead to segmentation
faults or other program crashes at run-time.

  
Your **book** program must include the following structs (typedef-ed
appropriately):

| **Structure Name**    | **Fields**         | **Functionality**                                            |
| :-------------------- | :----------------- | :----------------------------------------------------------- |
| \_Book (typedef Book) | int characterCount | Holds the total number of characters in the book’s contents. |
|                       | int lineCount      | Holds the total number of lines in the book’s contents.      |
|                       | char \*\*lines     | Holds all the lines of the book as strings.                  |

Your **book** program must include the following functions:

| **Requirement**  | **Conditions**                                                                          |
| :--------------- | :-------------------------------------------------------------------------------------- |
| Function         | Book\* make\_book(int)                                                                  |
| Input Parameters | An integer representing the maximum number of lines your book can hold.                 |
| Return Value     | A pointer to an initialized Book.                                                       |
| Notes            | An initialized book has no lines, but can hold up to the maximum provided. Character and line counts should be 0.                                                  |

| **Requirement**  | **Conditions**                                                                          |
| :--------------- | :-------------------------------------------------------------------------------------- |
| Function         | void burn\_book(Book\*)                                                                 |
| Input Parameters | A pointer to a Book.                                                                    |
| Return Value     | None.                                                                                   |
| Notes            | This function should deallocate all of the lines in the Book, and then the Book itself. |


| **Requirement**  | **Conditions**                                                                          |
| :--------------- | :-------------------------------------------------------------------------------------- |
| Function         | bool save\_book(Book\*, char\*)                                                         |
| Input Parameters | A pointer to a Book and a string representing a file name.                              |
| Return Value     | Return true if the book’s contents were stored to a file successfully. Otherwise false. |
| Notes            | This function should create or open a file based on the file name and write all of the current contents of the provided Book to that file one line at a time.                  |

| **Requirement**  | **Conditions**                                                                          |
| :--------------- | :-------------------------------------------------------------------------------------- |
| Function         | bool fill\_book(Book\*, char\*)                                                         |
| Input Parameters | A pointer to a Book and a string representing a file name.                              |
| Return Value     | Return true if the book’s contents were read and stored successfully. Otherwise false.  |
| Notes            | This function should read from the file name provided and store each line in the provided Book.  |                                                                                  

| **Requirement**  | **Conditions**                                                                          |
| :--------------- | :-------------------------------------------------------------------------------------- |
| Function         | int edit\_book(Book\*, char\*)                                                          |
| Input Parameters | A pointer to a Book and a string representing a word.                                   |
| Return Value     | An integer value that represents how many lines were removed from the book.             |
| Notes            | This function should remove every line from the Book which contains the provided word.  |

| **Requirement**  | **Conditions**                                                                          |
| :--------------- | :-------------------------------------------------------------------------------------- |
| Function         | void read\_book(Book\*)                                                                 |
| Input Parameters | A pointer to a Book.                                                                    |
| Return Value     | None.                                                                                   |
| Notes            | This function should print the provided Book’s content to stdout line-by-line.          |

### Postconditions

The various return values are outlined in the table above. Any book
outputs to stdout or file streams must be printed exactly as stored. The
`CI/objects/book` directory has a series of files for you to compare
your outputs to. The input files for the two stories are named
`i_must_scream` and `shadow_over_innsmouth`. Files ending in
**.out_example** contain the output from a book with no edits (book was
read in, then immediately saved with **save_book**). Files ending in
**.edit_example** contain the output from a book which has been edited
(book was read in, edited, then saved with **save_book**). The test
word for `i_must_scream` is **hate** and the test word for
`shadow_over_innsmouth` is **without**. {- These words only apply to the pipeline testing script. You should try other words/text files yourself to make sure everything is working properly. -}

### Restrictions

None.

### File Requirements

This contract requires you to provide a C source file named `book.c`
and a C header file named `book.h`. Your header files should contain
your forward declarations, struct definitions and typedefs, as well as
any library imports (includes) you may need. Your source files must not
contain any main functions, or it will fail during testing.

Your source and header files should be placed in the `Lab4/book/`
directory in your GitLab repository.

### Testing

To test your code, you can compile your source files with the
`bookM.o` object file found in `CI/objects/book`. Your program can
then be executed as normal. The object file contains a main function, so
you do not need to provide your own. You will need to provide the story
text files. In order to execute the provided main function, a story file
name must be passed into the program as its first argument.

### Sample Inputs and Outputs

Sample inputs and outputs are available via the object files and via the
various files in `CI/objects/book`. When executed, they will output
success and error messages, along with the parameters used to test them.

## Calculator

### Problem

You must create a struct for holding calculation operations and data,
then write functions to load and run the calculation process.

### Preconditions

You are required to write an arithmetic calculator for handling add,
subtract, multiply, divide, and mod (remainder) operations across a
simple data set. You will create a struct for holding the math functions
(as an array of function pointers), a selection of operation inputs (an
array of integer arrays), as well as the lengths of those arrays. You
will then write a series of functions for creating a calculator, loading
the operation inputs, and then executing those inputs.

The input files must be read into your program via file I/O, where each
file contains 100 lines of integers, with 3 integers on each line. Each
line’s integers are represented as **op a b**, where **op** represents
an index in the function pointer list (to select the math function to
use), while **a** and **b** are the inputs to those functions, in order.
Once your program reads in the input, it should also have the capability
of performing all of the operations in order and printing them to
stdout. All printed values should be to 5 decimal places.

Your `calculator.h` header file will contain forward definitions,
struct definitions and typedefs, and any necessary library imports to
ensure the proper operation of your functions. You must also write an
accompanying `calculator.c` file containing all of the matching
function implementations. When you compile, you will need to include the
source file in your command in order to ensure the functions exist
during the linking process. You may include any additional helper
functions as you see fit, although they will likely not be necessary.
Since you are dealing with pointers, you will need to check all of your
pointers to ensure they are not null. Trying to perform operations on
null will lead to segmentation faults or other program crashes at
run-time.  


Your **calculator** program must include the following structs
(typedef-ed appropriately):

| **Structure Name**   | **Fields**                       | **Functionality**                                          |
| :------------------- | :------------------------------- | :--------------------------------------------------------- |
| \_Calculator         | double (\*\*operations)(int,int) | Holds a list of function pointers to math operations.      |
| (typedef Calculator) | int \*\*data                     | Holds the operational data from an input file.             |
|                      | int operationCount               | Holds the total number of operations in the Calculator.    |
|                      | int dataLength                   | Holds the total number of data points from the input file. |

Your **calculator** program must include the following functions:

| **Requirement**  | **Conditions**                                                                                   |
| :--------------- | :----------------------------------------------------------------------------------------------- |
| Function         | Calculator\* create\_calculator(double (\*\*)(int,int), int)                                     |
| Input Parameters | An array of function pointers representing math operations and the length of that array.         |
| Return Value     | An initialized Calculator.                                                                       |
| Notes            | An initialized Calculator has no data. The operations and operation count should be saved.       |

| **Requirement**  | **Conditions**                                                                                   |
| :--------------- | :----------------------------------------------------------------------------------------------- |
| Function         | bool load\_calculator\_data(Calculator\*, char\*)                                                |
| Input Parameters | A pointer to a Calculator and a string representing a file name.                                 |
| Return Value     | Return true if data is successfully read and stored in the calculator. Otherwise false.          |
| Notes            | This function should read the data from the provided file and store it in the Calculator.        |

| **Requirement**  | **Conditions**                                                                                   |
| :--------------- | :----------------------------------------------------------------------------------------------- |
| Function         | void run\_calculator(Calculator\*)                                                               |
| Input Parameters | A pointer to a Calculator.                                                                       |
| Return Value     | None.                                                                                            |
| Notes            | This function should perform all of the operations in order and print them to stdout.            |
|                  | Each output value should be printed to 5 decimal places.                                         |

| **Requirement**  | **Conditions**                                                                                   |
| :--------------- | :----------------------------------------------------------------------------------------------- |
| Function         | bool destroy\_calculator(Calculator\*)                                                           |
| Input Parameters | A pointer to a Calculator.                                                                       |
| Return Value     | Return true if the calculator is successfully freed from memory. Otherwise false.                |
| Notes            | This function should deallocate all of the data from the calculator, then the calculator itself. |

| **Requirement**  | **Conditions**                                                                                   |
| :--------------- | :----------------------------------------------------------------------------------------------- |
| Function         | double add\_calculator(int, int)                                                                 |
|                  | double sub\_calculator(int, int)                                                                 |
|                  | double mul\_calculator(int, int)                                                                 |
|                  | double div\_calculator(int, int)                                                                 |
|                  | double mod\_calculator(int, int)                                                                 |
| Input Parameters | An integer a and b.                                                                              |
| Return Value     | A double value representing the output of a op b.                                                |
| Notes            | The functions should each use their associated operator in \{+, -, *, /, \%\}.               |

### Postconditions

The various return values are outlined in the table above. There are two
main functions provided for testing: `calculatorM1.o` and
`calculatorM2.o`. Each of these main functions have a different
configuration of functions being initialized in your Calculator struct.
There are also two input files and their associated outputs with each
main function, labelled appropriately. In order for you to test these
files manually, you will need to compile your code with a main function,
then execute the compiled program with one of the inputs as the first
command line argument.

### Restrictions

None.

### File Requirements

This contract requires you to provide a C source file named
`calculator.c` and a C header file named `calculator.h`. Your header
files should contain your forward declarations, struct definitions and
typedefs, as well as any library imports (includes) you may need. Your
source files must not contain any main functions, or it will fail during
testing.

Your source and header files should be placed in the
`Lab4/calculator/` directory in your GitLab repository.

### Testing

To test your code, you can compile your source files with the
`calculatorM1.o` and/or `calculatorM2.o` object files found in
`CI/objects/calculator`. Your program can then be executed as normal.
The object files contain a main functions, so you do not need to provide
your own. You will need to provide the operation input files. In order
to execute the provided main function, an input file name must be passed
into the program as its first argument.

### Sample Inputs and Outputs

Sample inputs and outputs are available via the object files and various
input/output files in `CI/objects/calculator`. When executed, they
will output success and error messages, along with the parameters used
to test them.

# Submission

## Required Files

When submitting this lab, you must submit your C source and header files
only. Each file must be contained in the directory listed in the
structure requirement diagram below. These files include:

1.  `book.c`
2.  `book.h`
3.  `calculator.c`
4.  `calculator.h`

As with all labs, submitting anything other than what is required in
this section will cause the testing pipeline to fail.

## Submission Procedure and Expectations

Your code will be submitted to your Lab 4 GitLab repository using the
same method as outlined in the Lab Technical Document. Refer to that
document if you do not remember how to submit files via the GitLab
service. A link to your repository can be found in the **Lab4** subgroup
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
Lab4/
 ┣ book/
 ┃  ┣ book.c
 ┃  ┗ book.h
 ┗ calculator/
    ┣ calculator.c
    ┗ calculator.h
```


As with all labs, accuracy is incredibly important. When submitting any
code for labs in this class, you *must* adhere to the directory
structure and naming requirements in the above diagram. Failure to do so
will cause the testing pipeline to fail.

Remember to remove `Lab4/delete_this_file` from your repository
using <kbd>git rm</kbd> to avoid any pipeline failures. Make sure there are
other files in your `Lab4/` directory before removing this file to
avoid any issues.
