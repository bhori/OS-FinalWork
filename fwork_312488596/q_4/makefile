CC=gcc
FLAGS=-g -Wall

dir_traversal: dir_traversal.o
	$(CC) $(FLAGS) -o dir_traversal dir_traversal.o

dir_traversal.o: dir_traversal.c
	$(CC) $(FLAGS) -fPIC -c dir_traversal.c

.PHONY: clean

clean:
	rm -f *.o *.out dir_traversal