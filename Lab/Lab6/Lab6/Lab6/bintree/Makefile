COMPILER = gcc

CSTD = --std=c18

all : bintree intree pretree posttree revtree

bintree : bintree.o bintreeM.o
	$(COMPILER) $(CSTD) bintree.o bintreeM.o -o bintree

intree : bintree.o intreeM.o
	$(COMPILER) $(CSTD) bintree.o intreeM.o -o intree

pretree : bintree.o pretreeM.o
	$(COMPILER) $(CSTD) bintree.o pretreeM.o -o pretree

posttree : bintree.o posttreeM.o
	$(COMPILER) $(CSTD) bintree.o posttreeM.o -o posttree

revtree : bintree.o revtreeM.o
	$(COMPILER) $(CSTD) bintree.o revtreeM.o -o revtree

bintree.o : bintree.c bintree.h
	$(COMPILER) $(CSTD) -c -g bintree.c

clean :
	rm -f bintree
	rm -f intree pretree posttree revtree
	rm -f *.o
