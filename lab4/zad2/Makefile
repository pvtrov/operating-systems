CC = gcc
CFLAGS = -Wall -g

all:
	make run
	make clean

run:
	$(CC) $(FLAGS) main4_2.c -o main4_2

clean:
	rm -rf main4_2

cleanTXT:
	rm *.txt

test:
	make cleanTXT

	make run
	./main4_2 >> raport2.txt

	make clean