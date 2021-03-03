/*
** EPITECH PROJECT, 2021
** nm [WSL: Ubuntu]
** File description:
** utilities
*/

#include "nm.h"

bool check_size(Elf64_Ehdr *ehdr, Elf64_Shdr **shdr, char **tab, size_t size)
{
    void *addr = ehdr;

    if (size < ehdr->e_shoff)
        return true;
    *shdr = addr + ehdr->e_shoff;
    if (size < (*shdr)[ehdr->e_shstrndx].sh_offset)
        return true;
    *tab = addr + (*shdr)[ehdr->e_shstrndx].sh_offset;
    return false;
}

bool check_size32(Elf32_Ehdr *ehdr, Elf32_Shdr **shdr, char **tab, size_t size)
{
    void *addr = ehdr;

    if (size < ehdr->e_shoff)
        return true;
    *shdr = addr + ehdr->e_shoff;
    if (size < (*shdr)[ehdr->e_shstrndx].sh_offset)
        return true;
    *tab = addr + (*shdr)[ehdr->e_shstrndx].sh_offset;
    return false;
}