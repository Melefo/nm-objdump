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
            printf(" ");
    }
}

bool blacklist_section(char *name, size_t size)
{
    if (name[0] == '\0')
        return true;
    if (size == 0)
        return true;
    if (strcmp(name, ".shstrtab") == 0)
        return true;
    if (strcmp(name, ".strtab") == 0)
        return true;
    if (strcmp(name, ".symtab") == 0)
        return true;
    if (strcmp(name, ".bss") == 0)
        return true;
    if (strncmp(name, ".rela.", 6) == 0)
        return true;
    return false;
}

int padding(Elf64_Xword n)
{
    int nbr = 0;

    while (n != 0) {
        n /= 16;
        nbr += 1;
    }
    if (nbr < 4)
        return 4;
    return nbr;
}

void print_sections(Elf64_Ehdr *ehdr)
{
    Elf64_Shdr *shdr = (void *)ehdr + ehdr->e_shoff;
    char *shstrtab = (void *)ehdr + shdr[ehdr->e_shstrndx].sh_offset;
    void *ptr = ehdr;

    for (int i = 0; i < ehdr->e_shnum; i++)
    {
        if (blacklist_section(shstrtab + shdr[i].sh_name, shdr[i].sh_size))
            continue;
        printf("Contents of section %s:\n", shstrtab + shdr[i].sh_name);
        for (Elf64_Xword j = 0; j < shdr[i].sh_size; j += 16)
        {
            printf(" %0*lx ", padding(shdr[i].sh_size), shdr[i].sh_addr + j);
            print_data(ptr + shdr[i].sh_offset + j, shdr[i].sh_size - j);
            printf("\n");
        }
    }
}

void print_sections32(Elf32_Ehdr *ehdr)
{
    Elf32_Shdr *shdr = (void *)ehdr + ehdr->e_shoff;
    char *shstrtab = (void *)ehdr + shdr[ehdr->e_shstrndx].sh_offset;
    void *ptr = ehdr;

    for (int i = 0; i < ehdr->e_shnum; i++)
    {
        if (blacklist_section(shstrtab + shdr[i].sh_name, shdr[i].sh_size))
            continue;
        printf("Contents of section %s:\n", shstrtab + shdr[i].sh_name);
        for (Elf32_Xword j = 0; j < shdr[i].sh_size; j += 16)
        {
            printf(" %0*lx ", padding(shdr[i].sh_size), shdr[i].sh_addr + j);
            print_data(ptr + shdr[i].sh_offset + j, shdr[i].sh_size - j);
            printf("\n");
        }
    }
}