/*
** EPITECH PROJECT, 2021
** objdump [WSL: Ubuntu]
** File description:
** sections
*/

#include <stdio.h>
#include "objdump.h"

void print_sections(Elf64_Ehdr *header)
{
    Elf64_Shdr *shdr = (void *)header + header->e_shoff;
    char *shstrtab = (void *)header + shdr[header->e_shstrndx].sh_offset;

    for (int i = 0; i < header->e_shnum; i++)
    {
        printf("Contents of section %s:\n", shstrtab + shdr[i].sh_name);
        for (Elf64_Xword j = 0; j < shdr[i].sh_size; j += 16)
        {
            printf(" %04lx ", shdr[i].sh_addr + j);
            printf("\n");
        }
    }
}