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

void objdump_arch(Elf64_Ehdr *header, char *file)
{
    print_header(header, file);

    if (header->e_ident[EI_CLASS] == ELFCLASS64)
        print_sections(header);
    else
        print_sections32((Elf32_Ehdr *)header);
}

bool objdump(char *file)
{
    size_t size;
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