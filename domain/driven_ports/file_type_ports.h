
#ifndef FILE_TYPE_PORT
 #define FILE_TYPE_PORT

#include "../../tools/lib.h"

int file_type(char **file, size_t size);

 #ifdef ELF_SUPPORT
  #include "../../adapters/driving_adapters/elf_adapter.h"
 #endif

#endif