#include "elf_adapter.h"


#define DEBUG

static int elf_section_header_32(char *file, const size_t size) {

    Elf32_Shdr *elf_section_header = (Elf32_Phdr*)file;
    printf("ELF section header\n");
#ifdef DEBUG
    printf("%x sh_name\n", elf_section_header->sh_name); // section name
    printf("%x sh_type\n", elf_section_header->sh_type); // 0 = inactive, 1 = program data, 2 = symbol table, 3 = string table, 4 = relocation entries with explicit addends, 5 = symbol hash table, 6 = dynamic linking information, 7 = notes, 8 = program space with no data, 9 = relocation entries, 10 = reserved, 11 = dynamic linker symbol table, 14 = array of constructors, 15 = array of destructors, 16 = array of pre-constructors, 17 = section group, 18 = extended section indices, 19 = number of defined types
    printf("%x sh_flags\n", elf_section_header->sh_flags); // 1 = writable, 2 = occupied, 4 = executable, 0xf0000000 = processor-specific
    printf("%x sh_addr\n", elf_section_header->sh_addr); // virtual address in memory
    printf("%x sh_offset\n", elf_section_header->sh_offset); // offset in file
    printf("%x sh_size\n", elf_section_header->sh_size); // size of section in file
    printf("%x sh_link\n", elf_section_header->sh_link); // section header table index link
    printf("%x sh_info\n", elf_section_header->sh_info); // extra information
    printf("%x sh_addralign\n", elf_section_header->sh_addralign); // 0 = no alignment, otherwise must be a power of 2
    printf("%x sh_entsize\n", elf_section_header->sh_entsize); // size of entries, 0 if section has no table
#endif
    return 0;
}


static int elf_section_header_64(char *file, const size_t size, char *strtab) {

    Elf64_Shdr *elf_section_header = (Elf32_Phdr*)file;
    printf("==========\nELF section header\n==========\n");
#ifdef DEBUG
    printf("%s sh_name\n", strtab + elf_section_header->sh_name); // section name
    printf("%x sh_type\n", elf_section_header->sh_type); // 0 = inactive, 1 = program data, 2 = symbol table, 3 = string table, 4 = relocation entries with explicit addends, 5 = symbol hash table, 6 = dynamic linking information, 7 = notes, 8 = program space with no data, 9 = relocation entries, 10 = reserved, 11 = dynamic linker symbol table, 14 = array of constructors, 15 = array of destructors, 16 = array of pre-constructors, 17 = section group, 18 = extended section indices, 19 = number of defined types
    printf("%x sh_flags\n", elf_section_header->sh_flags); // 1 = writable, 2 = occupied, 4 = executable, 0xf0000000 = processor-specific
    printf("%x sh_addr\n", elf_section_header->sh_addr); // virtual address in memory
    printf("%x sh_offset\n", elf_section_header->sh_offset); // offset in file
    printf("%x sh_size\n", elf_section_header->sh_size); // size of section in file
    printf("%x sh_link\n", elf_section_header->sh_link); // section header table index link
    printf("%x sh_info\n", elf_section_header->sh_info); // extra information
    printf("%x sh_addralign\n", elf_section_header->sh_addralign); // 0 = no alignment, otherwise must be a power of 2
    printf("%x sh_entsize\n", elf_section_header->sh_entsize); // size of entries, 0 if section has no table
#endif
    return 0;
}

static int elf_program_header_32(char *file, const size_t size) {

    Elf32_Phdr *elf_program_header = (Elf32_Phdr*)file;
    printf("==========\nELF program header\n==========\n");
#ifdef DEBUG    
    printf("%x p_type\n", elf_program_header->p_type); // 0 = unused, 1 = loadable segment, 2 = dynamic linking tables, 3 = program interpreter path name, 4 = note sections, 5 = unspecified semantics, 6 = program header table, 7 = thread-local storage template, 8 = thread-local storage, 9 = OS-specific semantics
    printf("%x p_offset\n", elf_program_header->p_offset); // offset in file
    printf("%x p_vaddr\n", elf_program_header->p_vaddr); // virtual address in memory
    printf("%x p_paddr\n", elf_program_header->p_paddr); // reserved
    printf("%x p_filesz\n", elf_program_header->p_filesz); // size of segment in file
    printf("%x p_memsz\n", elf_program_header->p_memsz); // size of segment in memory
    printf("%x p_flags\n", elf_program_header->p_flags); // 1 = executable, 2 = writable, 4 = readable
    printf("%x p_align\n", elf_program_header->p_align); // 0 = no alignment, otherwise must be a power of 2
#endif
    return 0;
}

static int elf_program_header_64(char *file, const size_t size) {

    Elf64_Phdr *elf_program_header = (Elf64_Phdr*)file;
    printf("==========\nELF program header\n==========\n");
#ifdef DEBUG
    printf("%x p_type\n", elf_program_header->p_type); // 0 = unused, 1 = loadable segment, 2 = dynamic linking tables, 3 = program interpreter path name, 4 = note sections, 5 = unspecified semantics, 6 = program header table, 7 = thread-local storage template, 8 = thread-local storage, 9 = OS-specific semantics
    printf("%x p_offset\n", elf_program_header->p_offset); // offset in file
    printf("%x p_vaddr\n", elf_program_header->p_vaddr); // virtual address in memory
    printf("%x p_paddr\n", elf_program_header->p_paddr); // reserved
    printf("%x p_filesz\n", elf_program_header->p_filesz); // size of segment in file
    printf("%x p_memsz\n", elf_program_header->p_memsz); // size of segment in memory
    printf("%x p_align\n", elf_program_header->p_align); // 0 = no alignment, otherwise must be a power of 2
#endif
    return 0;
}

static int elf_file_header(char *header) {

    printf("==========\nELF file header\n==========\n");
#ifdef DEBUG
    printf("%x magic number\n", *(int*)header);
    printf("%x class\n", header[EI_CLASS]); // 1 = 32 bits, 2 = 64 bits
    printf("%x data\n", header[EI_DATA]); // 1 = little endian, 2 = big endian
    printf("%x version\n", header[EI_VERSION]); // 1 = original, 2 = current
    printf("%x OS/ABI\n", header[EI_OSABI]); // 0 = System V, 1 = HP-UX, 2 = NetBSD, 3 = Linux, 4 = GNU Hurd, 6 = Solaris, 7 = AIX, 8 = IRIX, 9 = FreeBSD, 10 = Tru64, 11 = Novell Modesto, 12 = OpenBSD, 13 = OpenVMS, 14 = NonStop Kernel, 15 = AROS, 16 = Fenix OS, 17 = CloudABI, 18 = Stratus Technologies OpenVOS
    printf("%x ABI version\n", header[EI_ABIVERSION]);
    printf("%x padding\n", header[EI_PAD]);
#endif

    if (header[EI_CLASS] == ELFCLASS32) {
        Elf32_Ehdr *elf_header = (Elf32_Ehdr*)header;

#ifdef DEBUG
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
#endif

        printf("==========\n32 bits\n==========\n");

        Elf32_Addr entry_point = elf_header->e_entry;



    } else if (header[EI_CLASS] == ELFCLASS64) {
        Elf64_Ehdr *elf_header = (Elf64_Ehdr*)header;
        
#ifdef DEBUG
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
#endif
        
        printf("==========\n64 bits\n==========\n");

        Elf64_Addr entry_point = elf_header->e_entry;

        Elf64_Shdr *shstr = (Elf64_Shdr*)(header + elf_header->e_shoff + elf_header->e_shstrndx * elf_header->e_shentsize);
        char *shstrtab = header + shstr->sh_offset;

        for (int i = 0; i < elf_header->e_shnum; i++) {
            elf_section_header_64(header + elf_header->e_shoff + i * elf_header->e_shentsize, elf_header->e_shentsize, shstrtab);
        }

    } else {
        printf("Error: unsupported ELF class\n");
        exit(1);
    }
    return 0;
}

int elf_adapter(char *file, const size_t size) {
    printf("adapted GG\n");

    if (size > ELF64_HEADER_SIZE)
        elf_file_header(file);

    return 0;
}