exec : heap rheap

heap : heap.o heapM.o array_list.o
	gcc --std=c18 heap.o heapM.o array_list.o -o heap

rheap : heap.o rheapM.o array_list.o
	gcc --std=c18 heap.o rheapM.o array_list.o -o rheap

heap.o : heap.c heap.h
	gcc --std=c18 -Ilib -c heap.c -o heap.o

array_list.o : lib/array_list.c lib/array_list.h
	gcc --std=c18 -Ilib -c lib/array_list.c -o array_list.o

clean :
	rm -f *.o
	rm -f heap rheap
