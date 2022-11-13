all: clean build
build:
	gcc pb01.c heap.c -o pb01
	gcc pb02.c vector.c generic_heap.c -o pb02
clean:
	rm pb01 pb02
run1:
	valgrind ./pb01
run2:
	valgrind ./pb02