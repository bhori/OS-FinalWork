CC=gcc
FLAGS=-g -Wall

set_policy: set_policy.o
	$(CC) $(FLAGS) -o set_policy set_policy.o

set_policy.o: set_policy.c
	$(CC) $(FLAGS) -fPIC -c set_policy.c

.PHONY: clean

clean:
	rm -f *.o *.out set_policy