CC = gcc
CFLAGS = -Wall -g


compile:
		$(CC) $(FLAGS) main.c -o main

run:  compile
		./main a poem.txt
		@echo " " >> pomiar_zad_2.txt
		@echo "for 'a' and 'poem.txt" >> pomiar_zad_2.txt
		./main a poem.txt >> pomiar_zad_2.txt

clean:
		rm -f main
