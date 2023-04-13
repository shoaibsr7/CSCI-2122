COMPILER = gcc

CSTD = --std=c18

INCLUDE = -Ilib

stack : stack.o stackM.o linked_list.o
	$(COMPILER) $(CSTD) stack.o stackM.o linked_list.o -o stack

stack.o : stack.c stack.h
	$(COMPILER) $(CSTD) $(INCLUDE) -c stack.c

linked_list.o : linked_list.c linked_list.h
	$(COMPILER) $(CSTD) $(INCLUDE) -c linked_list.c -o linked_list.o

clean :
	rm -f stack.o stack
	rm -f linked_list.o
