CC = gcc
CFLAGS = -Wall -g
DIR := ${CURDIR}

all:
	make static
	make shared

static:
	$(CC) $(CFLAGS) -c first_library.c -o first_library.o
	ar rcs libfirst_library.a first_library.o

shared:
	$(CC) $(CFLAGS) -fPIC -c first_library.c -o first_library.o
	$(CC) $(CFLAGS) -shared -o libfirst_library.so first_library.o

clean:
	@rm -rf *.o *.a *.so  main
	@rm -rf *t.txt

test_static: static
	cp /home/mirabelka/CLionProjects/Operating_Systems_Course/lab1/files/*.txt ../zad2
	$(CC) -c main.c
	$(CC) main.o libfirst_library.a -o main

	rm -f raport2.txt

	@echo " " >> raport2.txt
	@echo "for small files: " >> raport2.txt
	@echo " " >> raport2.txt

	@echo "2 blocks, [2 files] [1 file]:" >> raport2.txt
	./main create_table 2 wc_files small0t.txt small1t.txt wc_files small2t.txt >> raport2.txt

	@echo "4 blocks, 2 files in each block, removing 3 blocks:" >> raport2.txt
	./main create_table 4 wc_files small1t.txt small2t.txt wc_files small1t.txt small2t.txt wc_files small1t.txt small2t.txt wc_files small1t.txt small2t.txt remove_block 0 remove_block 1 remove_block 2 >> raport2.txt

	@echo "5 blocks, adding and removing:" >> raport2.txt
	./main create_table 6 wc_files small1t.txt small2t.txt remove_block 0 wc_files small1t.txt small2t.txt remove_block 1 wc_files small1t.txt small2t.txt remove_block 2 wc_files small1t.txt small2t.txt remove_block 3 wc_files small1t.txt small2t.txt remove_block 4 >> raport2.txt

	@echo "for medium files: " >> raport2.txt
	@echo " " >> raport2.txt

	@echo "2 blocks, [2 files] [1 file]:" >> raport2.txt
	./main create_table 2 wc_files medium0t.txt medium1t.txt wc_files medium2t.txt >> raport2.txt

	@echo "4 blocks, 2 files in each block, removing 3 blocks:" >> raport2.txt
	./main create_table 4 wc_files medium1t.txt medium2t.txt wc_files medium1t.txt medium2t.txt wc_files medium1t.txt medium2t.txt wc_files medium1t.txt medium2t.txt remove_block 0 remove_block 1 remove_block 2 >> raport2.txt

	@echo "5 blocks, adding and removing:" >> raport2.txt
	./main create_table 6 wc_files medium1t.txt medium2t.txt remove_block 0 wc_files medium1t.txt medium2t.txt remove_block 1 wc_files medium1t.txt medium2t.txt remove_block 2 wc_files medium1t.txt medium2t.txt remove_block 3 wc_files medium1t.txt medium2t.txt remove_block 4 >> raport2.txt

	@echo "for large files: " >> raport2.txt
	@echo " " >> raport2.txt

	@echo "2 blocks, [2 files] [1 file]:" >> raport2.txt
	./main create_table 2 wc_files large0t.txt large1t.txt wc_files large2t.txt >> raport2.txt

	@echo "4 blocks, 2 files in each block, removing 3 blocks:" >> raport2.txt
	./main create_table 4 wc_files large1t.txt large2t.txt wc_files large1t.txt large2t.txt wc_files large1t.txt large2t.txt wc_files large1t.txt large2t.txt remove_block 0 remove_block 1 remove_block 2 >> raport2.txt

	@echo "5 blocks, adding and removing:" >> raport2.txt
	./main create_table 6 wc_files large1t.txt large2t.txt remove_block 0 wc_files large1t.txt large2t.txt remove_block 1 wc_files large1t.txt large2t.txt remove_block 2 wc_files large1t.txt large2t.txt remove_block 3 wc_files large1t.txt large2t.txt remove_block 4 >> raport2.txt
