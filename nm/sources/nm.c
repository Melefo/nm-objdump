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

bool extract_symbols(Elf64_Ehdr *header, char *strtab)
{
    Elf64_Shdr *sections = (void *)header + header->e_shoff;

    for (int i = 0; i < header->e_shnum; i++)
    {
        Elf64_Sym *symtable = (void *)header + sections[i].sh_offset;

        if (sections[i].sh_type != SHT_SYMTAB)
            continue;
        for (Elf64_Xword j = 0; j < sections[i].sh_size / sections[i].sh_entsize; j++)
        {
            if (!strtab[symtable[j].st_name])
                continue;
            if (symtable[i].st_value)
                printf("%06lx %c %s\n", symtable[j].st_value, '?', &strtab[symtable[j].st_name]);
            else
                printf("%10c %s\n", '?', &strtab[symtable[j].st_name]);
        }
    }
    return false;
}

bool nm_64(Elf64_Ehdr *header, char *file)
{
    Elf64_Shdr *sections = (void *)header + header->e_shoff;
    char *shstrtab = (void *)header + sections[header->e_shstrndx].sh_offset;
    bool result = true;

    if (header->e_shstrndx == SHN_UNDEF)
    {
        fprintf(stdout, "nm: %s: no symbols\n", file);
        return false;
    }
    for (int i = 0; i < header->e_shnum; i++)
    {
        if (strcmp(shstrtab + sections[i].sh_name, ".strtab") == 0)
            result = extract_symbols(header, (void *)header + sections[i].sh_offset);
    }
    return result;
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