#include "book.h"

// _GNU_SOURCE is always placed before stdio.h
#define _GNU_SOURCE 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Book* make_book(int maxLines)
{
	Book* book = malloc(sizeof *book);

	if (book == NULL)
		return NULL;

	book->characterCount = 0;
	book->lineCount = 0;
//	create memory space of size book->lines filePointer
// 	to hold maximum number of lines in the memory
	book->lines = malloc(sizeof *(book->lines) * maxLines);

	return book;
}

void burn_book(Book* book)
{
	if(book == NULL)
	{
		return;
	}

	for (int i=0; i < book->lineCount; i++)
	{
		free(book->lines[i]);
	}

	free(book->lines);
	free(book);
}

bool save_book(Book* book, char* fileName)
{
	if (book == NULL || fileName == NULL)
	{
		return false;
	}

// 	w: writing only
// 	r: reading only
// 	a: apending only

	FILE* filePointer = fopen(fileName, "w");

	if(filePointer == NULL)
	{
		printf("SAVE_BOOK_ERROR: Could not open the file \"%s\".\n", fileName);
		exit(-1);
	}

	int i = 0;

//	The fputs() function writes a line of characters into file. It outputs to the stream
//	int fputs(const char *s, FILE *stream)

	while (i < book->lineCount && fputs(book->lines[i++], filePointer) >= 0 );
	fclose(filePointer);

	return true;
}

bool fill_book(Book* book, char* fileName)
{
	if(book == NULL || book->lines == NULL || fileName == NULL)
	{
		return false;
	}

	FILE* filePointer = fopen(fileName, "r");

	size_t length = 0;

	size_t characters = 0;

	if(filePointer == NULL)
	{
		printf("FILL_BOOK_ERROR: Could not open the file \"%s\"\n", fileName);
		exit(-1);
	}

	int i = 0;

// 	ssize_t getline (char **lineptr, size_t *n, FILE *stream)
// 	This function reads an entire line from stream and stores the text 
//	(including the newline and a terminating null character) in a buffer and 
//	storing the buffer address in *lineptr.

//	&(book->lines[i++]) : gives us the pointer to the memory and address of where
//  the memory is held

	while((characters = getline(&(book->lines[i++]), &length, filePointer)) != -1)
	{
		book->characterCount += characters;

		book->lineCount += 1;
	}
	fclose(filePointer);
	return true;
}

int edit_book(Book* book, char* word)
{
	if(book == NULL || book->lines == NULL || word == NULL)
	{
		return -1;
	}

//  dummy lines used to store the lines of the Book
	char** lines = malloc(sizeof *lines * book->lineCount);

//  vairable to store the number of lines right before the edit was made
//  in the book which will be used later to subtract from original lines to
//	give the line number of the edit that was made	
	int j = 0;

// 	copy of line count from book 
	int lineC = book->lineCount;

	book->characterCount = 0;

	for(int i=0; i < book->lineCount; i++)
	{
//		The strstr() function returns pointer to the first occurrence of the matched string 
//		in the given string. It is used to return substring from first match till 
//		the last character.

//		char *strstr(const char *string, const char *match)
//		string: It represents the full string from where substring will be searched.
//		match: It represents the substring to be searched in the full string.
		if(strstr(book->lines[i], word) == NULL)
		{
			lines[j++] = book->lines[i];
			book->characterCount += strlen(book->lines[i]);
		}
		else
		{
			free(book->lines[i]);
		}
		book->lines[i] = NULL;
	}
	free(book->lines);

	book->lines = lines;
	book->lineCount = j;
	return lineC-j;
}

void read_book(Book* book)
{
	if(book == NULL || book->lines == NULL)
	{
		return;
	}

	for(int i=0; i<book->lineCount; i++)
	{
		printf("%s", book->lines[i]);
	}
}
