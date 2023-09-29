
#include <stdlib.h>

#define ELF_SUPPORT

int file_handler(char **file, size_t size) {
    int magic_number = *(int*)*file;

#ifdef ELF_SUPPORT
    if (magic_number == *(int*)"\177ELF") {
        #include "../../adapters/driving_adapters/elf_handling_adapter.c"
        elf_handling_adapter(file, size);
        return 0;
    }
#endif

    printf("Unsupported file format\n");
    exit(1);
}
