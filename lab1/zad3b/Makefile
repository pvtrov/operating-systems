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
		cp /home/mirabelka/CLionProjects/Operating_Systems_Course/lab1/files/*.txt ../zad3b


		@echo "static test: optimalization level: -O0" >> raport3b.txt
		make static
		make -s static_report OPTIMALIZATION=0

		@echo "static test: optimalization level: -O2" >> raport3b.txt
		make static
		make -s static_report OPTIMALIZATION=2

		@echo "static test: optimalization level: -O2" >> raport3b.txt
		make static
		make -s static_report OPTIMALIZATION=2

		@echo "shared test: optimaloization level: -O0" >> raport3b.txt
		make shared
		make -s shared_report OPTIMALIZATION=0

		@echo "shared test: optimaloization level: -O1" >> raport3b.txt
		make shared
		make -s shared_report OPTIMALIZATION=1

		@echo "shared test: optimaloization level: -O2" >> raport3b.txt
		make shared
		make -s shared_report OPTIMALIZATION=2

		@echo "dynamic test: optimalization level: -O0" >> raport3b.txt
		make dynamic
		make -s dynamic_report OPTIMALIZATION=0

		@echo "dynamic test: optimalization level: -O1" >> raport3b.txt
		make dynamic
		make -s dynamic_report OPTIMALIZATION=1

		@echo "dynamic test: optimalization level: -O2" >> raport3b.txt
		make dynamic
		make -s dynamic_report OPTIMALIZATION=2

		rm -rf files temp main


dynamic_report:
		cp /home/mirabelka/CLionProjects/Operating_Systems_Course/lab1/files/*.txt ../zad3b

		$(CC) -c ../zad2/main.c
		$(CC) main.o ../zad2/libfirst_library.so -o main -O$(OPTIMALIZATION)

		@echo " " >> raport3b.txt
		@echo "for small files: " >> raport3b.txt
		@echo " " >> raport3b.txt


		@echo "5 blocks, adding and removing:" >> raport3b.txt
		./main create_table 6 wc_files small1t.txt small2t.txt remove_block 0 wc_files small1t.txt small2t.txt remove_block 1 wc_files small1t.txt small2t.txt remove_block 2 wc_files small1t.txt small2t.txt remove_block 3 wc_files small1t.txt small2t.txt remove_block 4 >> raport3b.txt

		@echo "for medium files: " >> raport3b.txt
		@echo " " >> raport3b.txt


		@echo "5 blocks, adding and removing:" >> raport3b.txt
		./main create_table 6 wc_files medium1t.txt medium2t.txt remove_block 0 wc_files medium1t.txt medium2t.txt remove_block 1 wc_files medium1t.txt medium2t.txt remove_block 2 wc_files medium1t.txt medium2t.txt remove_block 3 wc_files medium1t.txt medium2t.txt remove_block 4 >> raport3b.txt

		@echo "for large files: " >> raport3b.txt
		@echo " " >> raport3b.txt

		@echo "5 blocks, adding and removing:" >> raport3b.txt
		./main create_table 6 wc_files large1t.txt large2t.txt remove_block 0 wc_files large1t.txt large2t.txt remove_block 1 wc_files large1t.txt large2t.txt remove_block 2 wc_files large1t.txt large2t.txt remove_block 3 wc_files large1t.txt large2t.txt remove_block 4 >> raport3b.txt

static_report:
		cp /home/mirabelka/CLionProjects/Operating_Systems_Course/lab1/files/*.txt ../zad3b

		$(CC) -c ../zad2/main.c
		$(CC) main.o ../zad2/libfirst_library.a -o main -O$(OPTIMALIZATION)

		@echo " " >> raport3b.txt
		@echo "for small files: " >> raport3b.txt
		@echo " " >> raport3b.txt

		@echo "5 blocks, adding and removing:" >> raport3b.txt
		./main create_table 6 wc_files small1t.txt small2t.txt remove_block 0 wc_files small1t.txt small2t.txt remove_block 1 wc_files small1t.txt small2t.txt remove_block 2 wc_files small1t.txt small2t.txt remove_block 3 wc_files small1t.txt small2t.txt remove_block 4 >> raport3b.txt

		@echo "for medium files: " >> raport3b.txt
		@echo " " >> raport3b.txt

		@echo "5 blocks, adding and removing:" >> raport3b.txt
		./main create_table 6 wc_files medium1t.txt medium2t.txt remove_block 0 wc_files medium1t.txt medium2t.txt remove_block 1 wc_files medium1t.txt medium2t.txt remove_block 2 wc_files medium1t.txt medium2t.txt remove_block 3 wc_files medium1t.txt medium2t.txt remove_block 4 >> raport3b.txt

		@echo "for large files: " >> raport3b.txt
		@echo " " >> raport3b.txt

		@echo "5 blocks, adding and removing:" >> raport3b.txt
		./main create_table 6 wc_files large1t.txt large2t.txt remove_block 0 wc_files large1t.txt large2t.txt remove_block 1 wc_files large1t.txt large2t.txt remove_block 2 wc_files large1t.txt large2t.txt remove_block 3 wc_files large1t.txt large2t.txt remove_block 4 >> raport3b.txt

shared_report:

		cp /home/mirabelka/CLionProjects/Operating_Systems_Course/lab1/files/*.txt ../zad3b

		$(CC) -c ../zad2/main.c
		$(CC) main.o ../zad2/libfirst_library.so -o main -O$(OPTIMALIZATION)

		@echo " " >> raport3b.txt
		@echo "for small files: " >> raport3b.txt
		@echo " " >> raport3b.txt


		@echo "5 blocks, adding and removing:" >> raport3b.txt
		./main create_table 6 wc_files small1t.txt small2t.txt remove_block 0 wc_files small1t.txt small2t.txt remove_block 1 wc_files small1t.txt small2t.txt remove_block 2 wc_files small1t.txt small2t.txt remove_block 3 wc_files small1t.txt small2t.txt remove_block 4 >> raport3b.txt

		@echo "for medium files: " >> raport3b.txt
		@echo " " >> raport3b.txt

		@echo "5 blocks, adding and removing:" >> raport3b.txt
		./main create_table 6 wc_files medium1t.txt medium2t.txt remove_block 0 wc_files medium1t.txt medium2t.txt remove_block 1 wc_files medium1t.txt medium2t.txt remove_block 2 wc_files medium1t.txt medium2t.txt remove_block 3 wc_files medium1t.txt medium2t.txt remove_block 4 >> raport3b.txt

		@echo "for large files: " >> raport3b.txt
		@echo " " >> raport3b.txt

		@echo "5 blocks, adding and removing:" >> raport3b.txt
		./main create_table 6 wc_files large1t.txt large2t.txt remove_block 0 wc_files large1t.txt large2t.txt remove_block 1 wc_files large1t.txt large2t.txt remove_block 2 wc_files large1t.txt large2t.txt remove_block 3 wc_files large1t.txt large2t.txt remove_block 4 >> raport3b.txt
