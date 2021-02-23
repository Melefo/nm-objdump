/*
** EPITECH PROJECT, 2021
** B-PSU-400-NAN-4-1-nmobjdump-victor.trencic [WSL: Ubuntu]
** File description:
** nm
*/

#include <stdio.h>
#include <sys/mman.h>
#include <string.h>
#include "nm.h"

bool nm_32(Elf32_Ehdr *header)
{
    return true;
}

bool extract_symbols(void *strtab)
{
    return false;
}

bool nm_64(Elf64_Ehdr *header, char *file)
{
    Elf64_Shdr *sections = (void *)header + header->e_shoff;
    char *strtab = (void *)header + sections[header->e_shstrndx].sh_offset;

    if (header->e_shstrndx == SHN_UNDEF)
    {
        fprintf(stdout, "nm: %s: no symbols\n", file);
        return false;
    }
    for (int i = 0; i < header->e_shnum; i++)
    {
        if (strcmp(strtab + sections[i].sh_name, ".strtab") == 0)
            return extract_symbols(strtab + sections[i].sh_offset);
    }
    return true;
}

bool nm_arch(Elf64_Ehdr *header, char *file)
{
    if (header->e_ident[EI_CLASS] == ELFCLASS64)
        return nm_64(header, file);
    return nm_32((Elf32_Ehdr *)header);
}

bool nm(char *file)
{
    int size;
    char *buffer = buffer_file(file, &size);
    bool result = false;

    if (buffer == NULL)
        return true;
    if (check_header((Elf64_Ehdr *)buffer))
    {
        fprintf(stderr, "nm: %s: file format not recognized\n", file);
        result = true;
    }
    result = nm_arch((Elf64_Ehdr *)buffer, file);
    munmap(buffer, size);
    return result;
}