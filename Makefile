CC=gcc
CFLAGS=-Wall

all: virus

virus: $(wildcard *.c)
	$(CC) $(CFLAGS) -c $(wildcard *.c)
	$(CC) $(CFLAGS) -o virus $(wildcard *.o)

clean:
	rm -f virus *.o