#include "elf_adapter.h"

// static elf_section_header(){}

// static elf_program_header(){}

static int elf_file_header(char *file) {
    printf("%x magic number\n", *(int*)file);
    printf("%x class\n", file[EI_CLASS]); // 1 = 32 bits, 2 = 64 bits
    printf("%x data\n", file[EI_DATA]); // 1 = little endian, 2 = big endian
    printf("%x version\n", file[EI_VERSION]); // 1 = original, 2 = current
    printf("%x OS/ABI\n", file[EI_OSABI]); // 0 = System V, 1 = HP-UX, 2 = NetBSD, 3 = Linux, 4 = GNU Hurd, 6 = Solaris, 7 = AIX, 8 = IRIX, 9 = FreeBSD, 10 = Tru64, 11 = Novell Modesto, 12 = OpenBSD, 13 = OpenVMS, 14 = NonStop Kernel, 15 = AROS, 16 = Fenix OS, 17 = CloudABI, 18 = Stratus Technologies OpenVOS
    printf("%x ABI version\n", file[EI_ABIVERSION]);
    printf("%x padding\n", file[EI_PAD]);   

    if (file[EI_CLASS] == ELFCLASS32) {
        Elf32_Ehdr *elf_header = (Elf32_Ehdr*)file;
        
        printf("%x e_type\n", elf_header->e_type); // 1 = relocatable, 2 = executable, 3 = shared, 4 = core
        printf("%x e_machine\n", elf_header->e_machine); // 3 = x86, 62 = x86-64
        printf("%x e_version\n", elf_header->e_version); // 1 = original, 2 = current
        printf("%x e_entry\n", elf_header->e_entry); // entry point address
        printf("%x e_phoff\n", elf_header->e_phoff); // program header table offset
        printf("%x e_shoff\n", elf_header->e_shoff); // section header table offset
        printf("%x e_flags\n", elf_header->e_flags); // processor-specific flags
        printf("%x e_ehsize\n", elf_header->e_ehsize); // ELF header size
        printf("%x e_phentsize\n", elf_header->e_phentsize); // size of program header entry
        printf("%x e_phnum\n", elf_header->e_phnum); // number of program header entries
        printf("%x e_shentsize\n", elf_header->e_shentsize); // size of section header entry
        printf("%x e_shnum\n", elf_header->e_shnum); // number of section header entries
        printf("%x e_shstrndx\n", elf_header->e_shstrndx); // section header table's section header string table index
    } else if (file[EI_CLASS] == ELFCLASS64) {
        Elf64_Ehdr *elf_header = (Elf64_Ehdr*)file;
        
        printf("%x e_type\n", elf_header->e_type); // 1 = relocatable, 2 = executable, 3 = shared, 4 = core
        printf("%x e_machine\n", elf_header->e_machine); // 3 = x86, 62 = x86-64
        printf("%x e_version\n", elf_header->e_version); // 1 = original, 2 = current
        printf("%lx e_entry\n", elf_header->e_entry); // entry point address
        printf("%lx e_phoff\n", elf_header->e_phoff); // program header table offset
        printf("%lx e_shoff\n", elf_header->e_shoff); // section header table offset
        printf("%x e_flags\n", elf_header->e_flags); // processor-specific flags
        printf("%x e_ehsize\n", elf_header->e_ehsize); // ELF header size
        printf("%x e_phentsize\n", elf_header->e_phentsize); // size of program header entry
        printf("%x e_phnum\n", elf_header->e_phnum); // number of program header entries
        printf("%x e_shentsize\n", elf_header->e_shentsize); // size of section header entry
        printf("%x e_shnum\n", elf_header->e_shnum); // number of section header entries
        printf("%x e_shstrndx\n", elf_header->e_shstrndx); // section header table's section header string table index
    } else {
        printf("Error: unsupported ELF class\n");
        exit(1);
    }
    return 0;
}

int elf_adapter(char *file, size_t size) {
    printf("adapted GG\n");

    if (size > ELF64_HEADER_SIZE)
        elf_file_header(file);

    return 0;
}