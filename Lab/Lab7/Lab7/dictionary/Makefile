dictionary : dictionary.o objectFiles/dictM.o linked_list.o bintree.o queue.o array_list.o stack.o
	gcc --std=c18 -Ilib array_list.o linked_list.o queue.o stack.o bintree.o dictionary.o objectFiles/dictM.o -o dictionary

dictionary.o : dictionary.c dictionary.h
	gcc --std=c18 -Ilib -c dictionary.c -o dictionary.o

bintree.o : lib/bintree.h lib/bintree.c
	gcc --std=c18 -Ilib -c lib/bintree.c -o bintree.o

array_list.o : lib/array_list.h lib/array_list.c
	gcc --std=c18 -Ilib -c lib/array_list.c -o array_list.o

linked_list.o : lib/linked_list.h lib/linked_list.c
	gcc --std=c18 -Ilib -c lib/linked_list.c -o linked_list.o

stack.o : lib/stack.h lib/stack.c
	gcc --std=c18 -Ilib -c lib/stack.c -o stack.o

queue.o : lib/queue.c lib/queue.h
	gcc --std=c18 -Ilib -c lib/queue.c -o queue.o

clean :
	rm -f dictionary
	rm -f *.o
