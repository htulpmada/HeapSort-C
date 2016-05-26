HeapSort: HeapSort.c node.c node.h
	gcc -Wall -g -std=c99 -o HeapSort HeapSort.c node.c node.h 
clean:
	rm HeapSort
