CC=gcc
CFLAGS=-Wall

all: virus

virus: $(wildcard *.c) \
		$(wildcard /root/virus2/adapters/driving_adapters/*.c) \
		$(wildcard /root/virus2/domain/driving_ports/*.c)
	make -C /root/virus2/adapters/driving_adapters
	make -C /root/virus2/domain/driving_ports
	$(CC) $(CFLAGS) -c main.c
	$(CC) $(CFLAGS) -o virus main.o /root/virus2/adapters/driving_adapters/*.o /root/virus2/domain/driving_ports/*.o

clean:
	make -C /root/virus2/adapters/driving_adapters clean
	make -C /root/virus2/domain/driving_ports clean
	rm -f virus *.o
