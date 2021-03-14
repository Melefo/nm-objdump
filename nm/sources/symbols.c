/*
** EPITECH PROJECT, 2021
** nm [WSL: Ubuntu]
** File description:
** symbols
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "nm.h"

static type_t types[] = {
    {'B', SHT_NOBITS, SHF_ALLOC | SHF_WRITE},
    {'D', SHT_PROGBITS, SHF_ALLOC | SHF_WRITE},
    {'D', SHT_DYNAMIC, SHF_ALLOC | SHF_WRITE},
    {'D', SHT_INIT_ARRAY, SHF_ALLOC | SHF_WRITE},
    {'D', SHT_FINI_ARRAY, SHF_ALLOC | SHF_WRITE},
    {'N', SHT_PROGBITS, 0},
    {'R', SHT_PROGBITS, SHF_ALLOC},
    {'T', SHT_PROGBITS, SHF_ALLOC | SHF_EXECINSTR},
    {'\0', 0, 0}
};

char type_weak(Elf64_Sym *sym)
{
    if (ELF64_ST_TYPE(sym->st_info) == STT_OBJECT)
        return sym->st_shndx == SHN_UNDEF ? 'v' : 'V';
    return sym->st_shndx == SHN_UNDEF ? 'w' : 'W';
}

char sym_type(Elf64_Sym *sym, Elf64_Ehdr *ehdr)
{
    Elf64_Shdr *shdr = (void *)ehdr + ehdr->e_shoff;
    char result = '?';

    if (sym->st_shndx == SHN_COMMON)
        return 'C';
    if (ELF64_ST_BIND(sym->st_info) == STB_GNU_UNIQUE)
        return 'u';
    if (sym->st_shndx == SHN_UNDEF)
        result = 'U';
    for (int i = 0; types[i].c && result == '?'; i++)
        if (shdr[sym->st_shndx].sh_type == types[i].type \
        && shdr[sym->st_shndx].sh_flags == types[i].flags)
            result = types[i].c;
    if (ELF64_ST_BIND(sym->st_info) == STB_WEAK)
        return type_weak(sym);
    if (sym->st_shndx == SHN_ABS)
        result = 'A';
    if (ELF64_ST_BIND(sym->st_info) == STB_LOCAL && result != '?')
        result += 'a' - 'A';
    return result;
}

void print_symbols(node_t *list, Elf64_Ehdr *elf)
{
    while (list)
    {
        Elf64_Sym *sym = list->symbol;
        char *strtab = list->strtab;
        char *name = &strtab[sym->st_name];
        node_t *to_free = list;

        if (name[0] == '\0' || sym->st_info == STT_FILE)
        {
            list = list->next;
            free(to_free);
            continue;
        }
        if (sym->st_shndx != SHN_UNDEF)
            printf("%016lx %c %s\n", sym->st_value, sym_type(sym, elf), name);
        else
            printf("%18c %s\n", sym_type(sym, elf), name);
        list = list->next;
        free(to_free);
    }
}

node_t *extract_symbols(Elf64_Ehdr *header, char *strtab)
{
    Elf64_Shdr *sections = (void *)header + header->e_shoff;
    node_t *list = NULL;

    for (int i = 0; i < header->e_shnum; i++)
    {
        Elf64_Sym *symtable;
        Elf64_Xword max;

        if (sections[i].sh_type != SHT_SYMTAB)
            continue;
        symtable = (void *)header + sections[i].sh_offset;
        max = sections[i].sh_size / sections[i].sh_entsize;
        for (Elf64_Xword j = 0; j < max; j++)
            append_node(&list, create_node(&symtable[j], strtab));
    }
    return list;
}
