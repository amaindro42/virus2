#ifndef ELF_ADAPTER
 #define ELF_ADAPTER

#include <elf.h>

#include "../../tools/lib.h"

int elf_adapter(char *file, size_t size);

#define ELF32_HEADER_SIZE 52
#define ELF64_HEADER_SIZE 64 

#endif