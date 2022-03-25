CC =gcc
CFLAGS = -Wall -g

all: run

nftw_compile:
	$(CC) $(FLAGS) main.c -o main -D NFTW

readdir_compile:
	$(CC) $(FLAGS) main.c -o main -D READDIR

test:
	@echo "nftw: " >> raport3.txt
	make nftw_compile
	./main test1 >> raport3.txt
	@echo "   " >> raport3.txt

	@echo "readdir: " >> raport3.txt
	make readdir_compile
	./main test1 >> raport3.txt

clean:
	rm -rf main
