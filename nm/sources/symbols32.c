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

char type_weak32(Elf32_Sym *sym)
{
    if (ELF32_ST_TYPE(sym->st_info) == STT_OBJECT)
        return sym->st_shndx == SHN_UNDEF ? 'v' : 'V';
    return sym->st_shndx == SHN_UNDEF ? 'w' : 'W';
}

char sym_type32(Elf32_Sym *sym, Elf32_Ehdr *ehdr)
{
    Elf32_Shdr *shdr = (void *)ehdr + ehdr->e_shoff;
    char result = '?';

    if (sym->st_shndx == SHN_COMMON)
        return 'C';
    if (ELF32_ST_BIND(sym->st_info) == STB_GNU_UNIQUE)
        return 'u';
    if (sym->st_shndx == SHN_UNDEF)
        result = 'U';
    for (int i = 0; types[i].c && result == '?'; i++)
        if (shdr[sym->st_shndx].sh_type == types[i].type \
        && shdr[sym->st_shndx].sh_flags == types[i].flags)
            result = types[i].c;
    if (ELF32_ST_BIND(sym->st_info) == STB_WEAK)
        return type_weak32(sym);
    if (sym->st_shndx == SHN_ABS)
        result = 'A';
    if (ELF32_ST_BIND(sym->st_info) == STB_LOCAL && result != '?')
        result += 'a' - 'A';
    return result;
}

void print_symbols32(node_t *list, Elf32_Ehdr *elf)
{
    while (list)
    {
        Elf32_Sym *sym = (Elf32_Sym *)list->symbol;
        char *strtab = list->strtab;
        char *name = &strtab[sym->st_name];
        node_t *to_free = list;

        if (name[0] == '\0' || sym->st_info == STT_FILE)
        {
            list = list->next;
            free(to_free);
            continue;
        }
        if (sym->st_value)
            printf("%08x %c %s\n", sym->st_value, sym_type32(sym, elf), name);
        else
            printf("%10c %s\n", sym_type32(sym, elf), name);
        list = list->next;
        free(to_free);
    }
}

node_t *extract_symbols32(Elf32_Ehdr *header, char *strtab)
{
    Elf32_Shdr *sections = (void *)header + header->e_shoff;
    node_t *list = NULL;

    for (int i = 0; i < header->e_shnum; i++)
    {
        Elf32_Sym *symtable;
        Elf32_Xword max;

        if (sections[i].sh_type != SHT_SYMTAB)
            continue;
        symtable = (void *)header + sections[i].sh_offset;
        max = sections[i].sh_size / sections[i].sh_entsize;
        for (Elf32_Xword j = 0; j < max; j++)
            append_node(&list, create_node32(&symtable[j], strtab));
    }
    return list;
}
