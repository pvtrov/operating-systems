CC = gcc
CFLAGS = -Wall -g

all:
	make run_exec
	make run_fork
	make clean

run_exec:
	$(CC) $(FLAGS) main4_1.c -o main4_1 -ldl -D EXEC

run_fork:
	$(CC) $(FLAGS) main4_1.c -o main4_1 -ldl -D FORK


clean:
	rm -rf main4_1

cleanTXT:
	rm *_.txt

test:
	make cleanTXT

	@echo " FOR FORK " >> raport2_.txt
	@echo " " >> raport2_.txt

	@echo "~~~~~~~IGNORE TEST~~~~~" >> raport2_.txt
	make run_fork
	./main4_1 ignore >> raport2_.txt
	@echo "" >> raport2_.txt

	@echo "~~~~HANDLER TEST~~~~~~" >> raport2_.txt
	make run_fork
	./main4_1 handler >> raport2_.txt
	@echo "" >> raport2_.txt

	@echo "~~~~~~MASK TEST~~~~~~ " >> raport2_.txt
	make run_fork
	./main4_1 mask >> raport2_.txt
	@echo "" >> raport2_.txt


	@echo "~~~~~~PENDING TEST~~~~~ " >> raport2_.txt
	make run_fork
	./main4_1 pending >> raport2_.txt
	@echo "" >> raport2_.txt
	@echo "" >> raport2_.txt


	@echo " FOR EXEC " >> raport2_.txt

	@echo "~~~~~~~IGNORE TEST~~~~~" >> raport2_.txt
	make run_exec
	./main4_1 ignore >> raport2_.txt
	@echo "" >> raport2_.txt

	@echo "~~~~~~MASK TEST~~~~~~ " >> raport2_.txt
	make run_exec
	./main4_1 mask >> raport2_.txt
	@echo "" >> raport2_.txt


	@echo "~~~~~~PENDING TEST~~~~~ " >> raport2_.txt
	make run_exec
	./main4_1 pending >> raport2_.txt
	@echo "" >> raport2_.txt
	@echo "" >> raport2_.txt

	make clean


