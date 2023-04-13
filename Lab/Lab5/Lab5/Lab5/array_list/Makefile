COMPILER = gcc

CSTD = --std=c18

array_list : array_list.o arrayM.o
	$(COMPILER) $(CSTD) array_list.o arrayM.o -o array_list

array_list.o : array_list.c array_list.h
	$(COMPILER) $(CSTD) -c array_list.c -o array_list.o;

arrayM.o :
	printf "ERROR: You must include 'arrayM.o' in this directory in order to compile.\n"

clean :
	rm -f array_list
	rm -f array_list.o       
