COMPILER = gcc

CSTD = --std=c18

LIB = -lm

INCLUDE = -Ilib

queue : queue.o queueM.o linked_list.o
	$(COMPILER) $(CSTD) $(LIB)  queue.o queueM.o linked_list.o -o queue

queue.o : queue.c queue.h
	$(COMPILER) $(CSTD) $(LIB) $(INCLUDE) -c queue.c

linked_list.o : linked_list.c linked_list.h
	$(COMPILER) $(CSTD) $(LIB) $(INCLUDE) -c linked_list.c -o linked_list.o

clean : 
	rm -f queue.o queue
	rm -f linked_list.o
