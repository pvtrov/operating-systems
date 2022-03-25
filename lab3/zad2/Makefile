CC = gcc
CFLAGS = -Wall -g

all:
	make run
	make clean

run:
	$(CC) $(CFLAGS) main3_2.c -o main3_2

clean:
	rm -rf main3_2
	rm -rf a.out

cleanTXT:
	rm *.txt

test1:

	@echo "for rectangle width: 0.00000001 and 16 processes: " >> raport2.txt
	make run
	./main3_2 0.000000001 16 >> raport2.txt
	@echo "" >> raport2.txt
	make clean


test2:

	@echo "for rectangle width: 0.000000001 and 9 processes: " >> raport2.txt
	make run
	./main3_2 0.000000001 9 >> raport2.txt
	@echo "" >> raport2.txt
	make clean

tests:
	make cleanTXT
	make test1
	make test2