/*
** EPITECH PROJECT, 2021
** objdump [WSL: Ubuntu]
** File description:
** sections
*/

#include <stdio.h>
#include <string.h>
#include "objdump.h"

void print_data(unsigned char *data, Elf64_Xword size)
{
    for (Elf64_Xword i = 0; i < 16; i++)
    {
        if (i < size)
            printf("%02x", data[i]);
        else
            printf("  ");
        if ((i + 1) % 4 == 0)
            printf(" ");
    }
    printf(" ");
    for (Elf64_Xword i = 0; i < 16; i++)
    {
        if (i < size)
            printf("%c", (data[i] >= ' ' && data[i] <= '~') ? data[i] : '.');
        else
            printf("  ");
    }
}

bool blacklist_section(char *name)
{
    if (name[0] == '\0')
        return true;
    if (strcmp(name, ".shstrtab") == 0)
        return true;
    if (strcmp(name, ".strtab") == 0)
        return true;
    if (strcmp(name, ".symtab") == 0)
        return true;
    if (strcmp(name, ".bss") == 0)
        return true;
    return false;
}

void print_sections(Elf64_Ehdr *header)
{
    Elf64_Shdr *shdr = (void *)header + header->e_shoff;
    char *shstrtab = (void *)header + shdr[header->e_shstrndx].sh_offset;

    for (int i = 0; i < header->e_shnum; i++)
    {
        if (blacklist_section(shstrtab + shdr[i].sh_name))
            continue;
        printf("Contents of section %s:\n", shstrtab + shdr[i].sh_name);
        for (Elf64_Xword j = 0; j < shdr[i].sh_size; j += 16)
        {
            printf(" %04lx ", shdr[i].sh_addr + j);
            print_data((void *)header + shdr[i].sh_offset + j, shdr[i].sh_size - j);
            printf("\n");
        }
    }
}