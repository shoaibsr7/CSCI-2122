COMPILER = gcc

CSTD = --std=c18

LIB = -Ilib

all : search dfs bfs

search : objectFiles/searchM.o search.o linked_list.o queue.o stack.o
	$(COMPILER) $(CSTD) $(LIB) linked_list.o queue.o stack.o search.o objectFiles/searchM.o -o search

bfs : search.o linked_list.o queue.o stack.o objectFiles/bfsM.o
	$(COMPILER) $(CSTD) $(LIB) linked_list.o queue.o stack.o search.o objectFiles/bfsM.o -o bfs

dfs : search.o linked_list.o queue.o stack.o objectFiles/dfsM.o
	$(COMPILER) $(CSTD) $(LIB) linked_list.o queue.o stack.o search.o objectFiles/dfsM.o -o dfs

search.o : bintree.c bintree.h
	$(COMPILER) $(CSTD) -c bintree.c -o search.o

linked_list.o : lib/linked_list.c lib/linked_list.h
	$(COMPILER) $(CSTD) $(LIB) -c lib/linked_list.c -o linked_list.o

stack.o : lib/stack.c lib/stack.h
	$(COMPILER) $(CSTD) $(LIB) -c lib/stack.c -o stack.o

queue.o : lib/queue.c lib/queue.h
	$(COMPILER) $(CSTD) $(LIB) -c lib/queue.c -o queue.o

clean : 
	rm -f search bfs dfs
	rm -f *.o
