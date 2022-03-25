CC = gcc
CFLAGS = -Wall -g

all:
	make run
	make clean

run:
	$(CC) $(FLAGS) main3_1.c -o main3_1

clean:
	rm -rf main3_1

cleanTXT:
	rm *.txt

test:
	make cleanTXT

	@echo "for n = 3: " >> raport1.txt
	make run
	./main3_1 3 >> raport1.txt
	@echo "" >> raport1.txt

	@echo "for n = 4: " >> raport1.txt
	make run
	./main3_1 4 >> raport1.txt
	@echo "" >> raport1.txt

	make clean