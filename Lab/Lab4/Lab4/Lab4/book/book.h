#ifndef __BOOK_HEADER
#define __BOOK_HEADER

#include <stdbool.h>

typedef struct _BOOK
{
	int characterCount;
	int lineCount;
	char** lines;
} Book;

Book* make_book(int);
void burn_book(Book*);
bool save_book(Book*, char*);
bool fill_book(Book*, char*);
int edit_book(Book*, char*);
void read_book(Book*);

#endif
