CC=gcc
FLAGS=-g -Wall

all: server client

server: server.o
	(CC) (FLAGS) -o server server.o

client: client.o
	(CC) (FLAGS) -o client client.o

server.o: server.c
	(CC) (FLAGS) -fPIC -c server.c

client.o: client.c
	(CC) (FLAGS) -fPIC -c client.c

.PHONY: all clean

clean:
	rm -f *.o *.out server client