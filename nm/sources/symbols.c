/*
** EPITECH PROJECT, 2021
** nm [WSL: Ubuntu]
** File description:
** symbols
*/

#include <stdio.h>
#include <string.h>
#include "nm.h"

char sym_type_spec(Elf64_Sym *sym, Elf64_Ehdr *ehdr)
{
    Elf64_Shdr *shdr = (void *)ehdr + ehdr->e_shoff;
    char *shstrtab = (void *)ehdr + shdr[ehdr->e_shstrndx].sh_offset;

    if (ELF64_ST_TYPE(sym->st_info) == STT_COMMON)
        return 'C';
    if (strcmp(shstrtab + shdr[sym->st_shndx].sh_name, ".debug") == 0)
        return 'N';
    if (sym->st_shndx == SHN_UNDEF)
        return 'U';
    return '?';
}

char sym_type(Elf64_Sym *sym, Elf64_Ehdr *ehdr)
{
    Elf64_Shdr *shdr = (void *)ehdr + ehdr->e_shoff;
    char *shstrtab = (void *)ehdr + shdr[ehdr->e_shstrndx].sh_offset;

    if (sym->st_shndx == SHN_ABS)
        return ELF64_ST_BIND(sym->st_info) == STB_GLOBAL ? 'A' : 'a';
    if (strcmp(shstrtab + shdr[sym->st_shndx].sh_name, ".bss") == 0)
        return ELF64_ST_BIND(sym->st_info) == STB_GLOBAL ? 'B' : 'b';
    if (strcmp(shstrtab + shdr[sym->st_shndx].sh_name, ".data") == 0 \
    || strcmp(shstrtab + shdr[sym->st_shndx].sh_name, ".data1") == 0)
        return ELF64_ST_BIND(sym->st_info) == STB_GLOBAL ? 'D' : 'd';
    if (strcmp(shstrtab + shdr[sym->st_shndx].sh_name, ".rodata") == 0 \
    || strcmp(shstrtab + shdr[sym->st_shndx].sh_name, ".rodata1") == 0)
        return ELF64_ST_BIND(sym->st_info) == STB_GLOBAL ? 'R' : 'r';
    if (strcmp(shstrtab + shdr[sym->st_shndx].sh_name, ".text") == 0)
        return ELF64_ST_BIND(sym->st_info) == STB_GLOBAL ? 'T' : 't';
    if (ELF64_ST_BIND(sym->st_info) == STB_WEAK)
        return ELF64_ST_BIND(sym->st_info) == STB_GLOBAL ? 'W' : 'w';
    // 'G' ? 'i' ? 'I' ? 'n' ? 'p' ? 'S' ? 'u' ? '-' ?
    return sym_type_spec(sym, ehdr);
}

void print_sym(char *strtab, Elf64_Sym *sym, Elf64_Ehdr *elf)
{
    char *name = &strtab[sym->st_name];
    if (name[0] == '\0')
        return;
    if (sym->st_value)
        printf("%016lx %c %s\n", sym->st_value, sym_type(sym, elf), name);
    else
        printf("%18c %s\n", sym_type(sym, elf), name);
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
            print_sym(strtab, &symtable[j], header);
    }
    return false;
}
