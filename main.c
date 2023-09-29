#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include "domain/driven_ports/elf_handling_ports.c"

char *file_open(char *filename, int *fd, struct stat *sb) {

    *fd = open(filename, O_RDWR);
    if (*fd == -1) {
        printf("Error: cannot open file %s\n", filename);
        exit(1);
    }

    if (fstat(*fd, sb) == -1) {
        printf("Error: cannot get file size\n");
        exit(1);
    }

    char *addr = mmap(NULL, sb->st_size, PROT_READ | PROT_WRITE, MAP_PRIVATE, *fd, 0);
    if (addr == MAP_FAILED) {
        printf("Error: cannot mmap file\n");
        exit(1);
    }

    return addr;
}

int file_close(char *addr, int fd, struct stat *sb) {
    if (munmap(addr, sb->st_size) == -1) {
        printf("Error: cannot munmap file\n");
        exit(1);
    }

    if (close(fd) == -1) {
        printf("Error: cannot close file\n");
        exit(1);
    }

    return 0;
}

int main(int ac, char **av) {
    int fd;
    struct stat sb;
    
    if (ac != 2) {
        printf("Usage: %s <file>\n", av[0]);
        exit(1);
    }

    char *addr = file_open(av[1], &fd, &sb);

    if (file_handler(&addr, sb.st_size) != 0) {
        printf("An error occured\n");
        exit(1);
    }

    return file_close(addr, fd, &sb);
}