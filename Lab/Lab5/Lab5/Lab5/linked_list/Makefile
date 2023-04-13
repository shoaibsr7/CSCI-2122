COMPILER = gcc

CSTD = --std=c18

linked_list : linked_list.o linkedM.o
	$(COMPILER) $(CSTD) linked_list.o linkedM.o -o linked_list

linked_list.o : linked_list.c linked_list.h
	$(COMPILER) $(CSTD) -c linked_list.c -o linked_list.o

linkedM.o : 
	printf "You must include 'linkedM.o' in this directory in order to compile.\n"

clean :
	rm -f linked_list
	rm -f linked_list.o
