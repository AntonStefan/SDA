all: clean build run
build:
	gcc main.c Generic_Heap.c vector.c Gen_Utility.c WGraph.c -o exe
clean:
	rm exe
run:
	valgrind -s ./exe