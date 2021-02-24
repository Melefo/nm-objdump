/*
** EPITECH PROJECT, 2021
** nm [WSL: Ubuntu]
** File description:
** symbols
*/

#include "nm.h"

void print_symbol(char *strtab, Elf64_Sym *sym)
{
    if (!strtab[sym->st_name])
        return;
    if (sym->st_value)
        printf("%016lx %c %s\n", sym->st_value, '?', &strtab[sym->st_name]);
    else
        printf("%18c %s\n", '?', &strtab[sym->st_name]);
}

bool extract_symbols(Elf64_Ehdr *header, char *strtab)
{
    Elf64_Shdr *sections = (void *)header + header->e_shoff;

    for (int i = 0; i < header->e_shnum; i++)
    {
        Elf64_Sym *symtable;
        Elf64_Xword max;

        if (sections[i].sh_type != SHT_SYMTAB)
            continue;
        symtable = (void *)header + sections[i].sh_offset;
        max = sections[i].sh_size / sections[i].sh_entsize;
        for (Elf64_Xword j = 0; j < max; j++)
            print_symbol(strtab, &symtable[j]);
    }
    return false;
}
