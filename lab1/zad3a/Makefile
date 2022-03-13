CC = gcc
CFLAGS = -Wall -std=gnu11

all:
		static shared dynamic

static:
		make -C ../zad2 static

shared:
		make -C ../zad2 shared

dynamic:
		make -C ../zad2 shared
		$(CC) $(CFLAGS) ../zad2/main.c -o main.o -ldl -D DYNAMIC

clean:
		make -C ../zad2 clean
		make -C ../zad2 clean
		rm -f *t.txt temp.txt main.o main
		make -C ../zad1 clean


test: clean
		cp /home/mirabelka/CLionProjects/Operating_Systems_Course/lab1/files/*.txt ../zad3a


		@echo "static test:" >> raport3a.txt
		make static
		make static_report

		@echo "shared test:" >> raport3a.txt
		make shared
		make dynamic_report

		@echo "dynamic test:" >> raport3a.txt
		make dynamic
		make dynamic_report

		rm -rf files temp main


dynamic_report:
		cp /home/mirabelka/CLionProjects/Operating_Systems_Course/lab1/files/*.txt ../zad3a

		$(CC) -c ../zad2/main.c
		$(CC) main.o ../zad2/libfirst_library.so -o main

		@echo " " >> raport3a.txt
		@echo "for small files: " >> raport3a.txt
		@echo " " >> raport3a.txt

		@echo "2 blocks, [2 files] [1 file]:" >> raport3a.txt
		./main create_table 2 wc_files small0t.txt small1t.txt wc_files small2t.txt >> raport3a.txt

		@echo "4 blocks, 2 files in each block, removing 3 blocks:" >> raport3a.txt
		./main create_table 4 wc_files small1t.txt small2t.txt wc_files small1t.txt small2t.txt wc_files small1t.txt small2t.txt wc_files small1t.txt small2t.txt remove_block 0 remove_block 1 remove_block 2 >> raport3a.txt

		@echo "5 blocks, adding and removing:" >> raport3a.txt
		./main create_table 6 wc_files small1t.txt small2t.txt remove_block 0 wc_files small1t.txt small2t.txt remove_block 1 wc_files small1t.txt small2t.txt remove_block 2 wc_files small1t.txt small2t.txt remove_block 3 wc_files small1t.txt small2t.txt remove_block 4 >> raport3a.txt

		@echo "for medium files: " >> raport3a.txt
		@echo " " >> raport3a.txt

		@echo "2 blocks, [2 files] [1 file]:" >> raport3a.txt
		./main create_table 2 wc_files medium0t.txt medium1t.txt wc_files medium2t.txt >> raport3a.txt

		@echo "4 blocks, 2 files in each block, removing 3 blocks:" >> raport3a.txt
		./main create_table 4 wc_files medium1t.txt medium2t.txt wc_files medium1t.txt medium2t.txt wc_files medium1t.txt medium2t.txt wc_files medium1t.txt medium2t.txt remove_block 0 remove_block 1 remove_block 2 >> raport3a.txt

		@echo "5 blocks, adding and removing:" >> raport3a.txt
		./main create_table 6 wc_files medium1t.txt medium2t.txt remove_block 0 wc_files medium1t.txt medium2t.txt remove_block 1 wc_files medium1t.txt medium2t.txt remove_block 2 wc_files medium1t.txt medium2t.txt remove_block 3 wc_files medium1t.txt medium2t.txt remove_block 4 >> raport3a.txt

		@echo "for large files: " >> raport3a.txt
		@echo " " >> raport3a.txt

		@echo "2 blocks, [2 files] [1 file]:" >> raport3a.txt
		./main create_table 2 wc_files large0t.txt large1t.txt wc_files large2t.txt >> raport3a.txt

		@echo "4 blocks, 2 files in each block, removing 3 blocks:" >> raport3a.txt
		./main create_table 4 wc_files large1t.txt large2t.txt wc_files large1t.txt large2t.txt wc_files large1t.txt large2t.txt wc_files large1t.txt large2t.txt remove_block 0 remove_block 1 remove_block 2 >> raport3a.txt

		@echo "5 blocks, adding and removing:" >> raport3a.txt
		./main create_table 6 wc_files large1t.txt large2t.txt remove_block 0 wc_files large1t.txt large2t.txt remove_block 1 wc_files large1t.txt large2t.txt remove_block 2 wc_files large1t.txt large2t.txt remove_block 3 wc_files large1t.txt large2t.txt remove_block 4 >> raport3a.txt

static_report:
		cp /home/mirabelka/CLionProjects/Operating_Systems_Course/lab1/files/*.txt ../zad3a

		$(CC) -c ../zad2/main.c
		$(CC) main.o ../zad2/libfirst_library.a -o main

		@echo " " >> raport3a.txt
		@echo "for small files: " >> raport3a.txt
		@echo " " >> raport3a.txt

		@echo "2 blocks, [2 files] [1 file]:" >> raport3a.txt
		./main create_table 2 wc_files small0t.txt small1t.txt wc_files small2t.txt >> raport3a.txt

		@echo "4 blocks, 2 files in each block, removing 3 blocks:" >> raport3a.txt
		./main create_table 4 wc_files small1t.txt small2t.txt wc_files small1t.txt small2t.txt wc_files small1t.txt small2t.txt wc_files small1t.txt small2t.txt remove_block 0 remove_block 1 remove_block 2 >> raport3a.txt

		@echo "5 blocks, adding and removing:" >> raport3a.txt
		./main create_table 6 wc_files small1t.txt small2t.txt remove_block 0 wc_files small1t.txt small2t.txt remove_block 1 wc_files small1t.txt small2t.txt remove_block 2 wc_files small1t.txt small2t.txt remove_block 3 wc_files small1t.txt small2t.txt remove_block 4 >> raport3a.txt

		@echo "for medium files: " >> raport3a.txt
		@echo " " >> raport3a.txt

		@echo "2 blocks, [2 files] [1 file]:" >> raport3a.txt
		./main create_table 2 wc_files medium0t.txt medium1t.txt wc_files medium2t.txt >> raport3a.txt

		@echo "4 blocks, 2 files in each block, removing 3 blocks:" >> raport3a.txt
		./main create_table 4 wc_files medium1t.txt medium2t.txt wc_files medium1t.txt medium2t.txt wc_files medium1t.txt medium2t.txt wc_files medium1t.txt medium2t.txt remove_block 0 remove_block 1 remove_block 2 >> raport3a.txt

		@echo "5 blocks, adding and removing:" >> raport3a.txt
		./main create_table 6 wc_files medium1t.txt medium2t.txt remove_block 0 wc_files medium1t.txt medium2t.txt remove_block 1 wc_files medium1t.txt medium2t.txt remove_block 2 wc_files medium1t.txt medium2t.txt remove_block 3 wc_files medium1t.txt medium2t.txt remove_block 4 >> raport3a.txt

		@echo "for large files: " >> raport3a.txt
		@echo " " >> raport3a.txt

		@echo "2 blocks, [2 files] [1 file]:" >> raport3a.txt
		./main create_table 2 wc_files large0t.txt large1t.txt wc_files large2t.txt >> raport3a.txt

		@echo "4 blocks, 2 files in each block, removing 3 blocks:" >> raport3a.txt
		./main create_table 4 wc_files large1t.txt large2t.txt wc_files large1t.txt large2t.txt wc_files large1t.txt large2t.txt wc_files large1t.txt large2t.txt remove_block 0 remove_block 1 remove_block 2 >> raport3a.txt

		@echo "5 blocks, adding and removing:" >> raport3a.txt
		./main create_table 6 wc_files large1t.txt large2t.txt remove_block 0 wc_files large1t.txt large2t.txt remove_block 1 wc_files large1t.txt large2t.txt remove_block 2 wc_files large1t.txt large2t.txt remove_block 3 wc_files large1t.txt large2t.txt remove_block 4 >> raport3a.txt




