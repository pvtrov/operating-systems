CC = gcc
CFLAGS = -Wall -g

all:
	make run_catcher
	make run_sender
	make clean

run_catcher:
	$(CC) $(FLAGS) catcher.c -o catcher


run_sender:
	$(CC) $(FLAGS) sender.c -o sender

clean:
	rm -rf catcher
	rm -rf sender

test:
	make all
