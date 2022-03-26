CC = gcc
CFLAGS = -Wall -g

all:
	make run


run:
	$(CC) $(CFLAGS) main3_3.c -o main3_3

clean:
	rm -rf main3_3
	rm -rf a.out

test:
	make run
	./main3_3 testDir kotek 4
	make clean