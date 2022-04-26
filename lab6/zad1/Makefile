CC = gcc
CFLAGS = -Wall -g

all: compile
	make clean

compile:
	gcc -Wall -g server.c -o server
	gcc -Wall -g client.c -o client

server:
	gcc -Wall -g server.c -o server
	./server

client:
	gcc -Wall -g client.c -o client
	./client

clean:
	rm -f server client