CC=gcc
CFLAGS=-Wall

all: virus

virus: main.c
	$(CC) $(CFLAGS) -o virus main.c

clean:
	rm -f virus
