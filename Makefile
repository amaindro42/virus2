CC=gcc
CFLAGS=-Wall

all: virus

virus: $(wildcard *.c)
	make -C /root/virus2/adapters/driving_adapters
	make -C /root/virus2/domain/driven_ports
	$(CC) $(CFLAGS) -c main.c
	$(CC) $(CFLAGS) -o virus main.o /root/virus2/adapters/driving_adapters/*.o /root/virus2/domain/driven_ports/*.o

clean:
	make -C /root/virus2/adapters/driving_adapters clean
	make -C /root/virus2/domain/driven_ports clean
	rm -f virus *.o
