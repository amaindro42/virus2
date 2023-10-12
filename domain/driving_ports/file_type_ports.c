#include "file_type_ports.h"

int file_type(char *file, const size_t size) {
    const int magic_number = *(int*)file;

#ifdef ELF_SUPPORT
    if (magic_number == *(int*)"\177ELF") {
        elf_adapter(file, size);
        return 0;
    }
#endif

    printf("Unsupported file format\n");
    exit(1);
}
