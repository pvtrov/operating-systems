CC = gcc
CFLAGS = -Wall -g

all:
	make run
	make clean

run:
	$(CC) $(FLAGS) main5_1.c -o main5_1

clean:
	rm -rf main5_1

test:
	make run
	./main5_1 commands.txt

	make clean