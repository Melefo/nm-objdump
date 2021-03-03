/*
** EPITECH PROJECT, 2021
** objdump [WSL: Ubuntu]
** File description:
** objdump
*/

#include <sys/mman.h>
#include <stddef.h>
#include <stdio.h>
#include "objdump.h"

bool objdump_32(Elf32_Ehdr *ehdr, char *file)
{
    header_t header = {
        ehdr->e_ident,
        ehdr->e_machine,
        ehdr->e_flags,
        ehdr->e_entry
    };

    print_header(header, file);
    print_sections32(ehdr);
    return false;
}

bool objdump_64(Elf64_Ehdr *ehdr, char *file)
{
    header_t header = {
        ehdr->e_ident,
        ehdr->e_machine,
        ehdr->e_flags,
        ehdr->e_entry
    };

    print_header(header, file);
    print_sections(ehdr);
    return false;
}

bool objdump_arch(Elf64_Ehdr *header, char *file)
{
    if (header->e_ident[EI_CLASS] == ELFCLASS64)
        return objdump_64(header, file);
    return objdump_32((Elf32_Ehdr *)header, file);
}

bool objdump(char *file)
{
    int size;
    char *buffer = buffer_file(file, &size);
    bool result = false;

    if (buffer == NULL)
        return true;
    if (check_header((Elf64_Ehdr *)buffer))
    {
        fprintf(stderr, "nm: %s: file format not recognized\n", file);
        return true;
    }
    objdump_arch((Elf64_Ehdr *)buffer, file);
    munmap(buffer, size);
    return result;
}