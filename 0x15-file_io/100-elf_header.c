#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <elf.h>
#include <string.h>
#include <errno.h>

#define USAGE "Usage: elf_header elf_filename\nDisplayed information: (no less, no more, do not include trailing whitespace)\n\tMagic\n\tClass\n\tData\n\tVersion\n\tOS/ABI\n\tABI Version\n\tType\n\tEntry point address\nFormat: the same as readelf -h (version 2.26.1)\nIf the file is not an ELF file, or on error, exit with status code 98 and display a comprehensive error message to stderr\n"

void print_error(char *msg) {
    fprintf(stderr, "%s: %s\n", msg, strerror(errno));
    exit(98);
}

void print_elf_header(Elf64_Ehdr *header) {
    printf("ELF Header:\n");
    printf("  Magic:   ");
    for (int i = 0; i < EI_NIDENT; i++) {
        printf("%02x ", header->e_ident[i]);
    }
    printf("\n");
    printf("  Class:                             %s\n", header->e_ident[EI_CLASS] == ELFCLASS32 ? "ELF32" : "ELF64");
    printf("  Data:                              %s\n", header->e_ident[EI_DATA] == ELFDATA2LSB ? "2's complement, little endian" : "2's complement, big endian");
    printf("  Version:                           %d%s\n", header->e_ident[EI_VERSION], header->e_ident[EI_VERSION] == EV_CURRENT ? " (current)" : "");
    printf("  OS/ABI:                            ");
    switch (header->e_ident[EI_OSABI]) {
        case ELFOSABI_SYSV:
            printf("UNIX - System V\n");
            break;
        case ELFOSABI_HPUX:
            printf("UNIX - HP-UX\n");
            break;
        case ELFOSABI_NETBSD:
            printf("UNIX - NetBSD\n");
            break;
        case ELFOSABI_LINUX:
            printf("UNIX - Linux\n");
            break;
        case ELFOSABI_SOLARIS:
            printf("UNIX - Solaris\n");
            break;
        case ELFOSABI_IRIX:
            printf("UNIX - IRIX\n");
            break;
        case ELFOSABI_FREEBSD:
            printf("UNIX - FreeBSD\n");
            break;
        case ELFOSABI_TRU64:
            printf("UNIX - TRU64\n");
            break;
        case ELFOSABI_ARM:
            printf("ARM\n");
            break;
        case ELFOSABI_STANDALONE:
            printf("Standalone App\n");
            break;
        default:
            printf("<unknown: %x>\n", header->e_ident[EI_OSABI]);
            break;
    }
    printf("  ABI Version:                       %d\n", header->e_ident[EI_ABIVERSION]);
    printf("  Type:                              ");
    switch (header->e_type) {
        case ET_NONE:
            printf("NONE (No file type)\n");
            break;
        case ET_REL:
            printf("REL (Relocatable file)\n");
            break;
        case ET_EXEC:
            printf("EXEC (Executable file)\n");
            break;
        case ET_DYN:
            printf("DYN (Shared object file)\n");
            break;
        case ET_CORE:
            printf("CORE (Core file)\n");
            break;
        default:
            printf("<unknown: %x>\n", header->e_type);
            break;
    }
    printf("  Entry point address:               0x%lx\n", header->e_entry);
}

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, USAGE);
        exit(98);
    }

    int fd = open(argv[1], O_RDONLY);
    if (fd == -1) {
        print_error(argv[1]);
    }

    Elf64_Ehdr header;
    if (read(fd, &header, sizeof(header)) != sizeof(header)) {
        print_error(argv[1]);
    }

    if (memcmp(header.e_ident, ELFMAG, SELFMAG) != 0) {
        fprintf(stderr, "%s: Not an ELF file\n", argv[1]);
        exit(98);
    }

    print_elf_header(&header);

    return 0;
}
