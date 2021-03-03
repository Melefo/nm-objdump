/*
** EPITECH PROJECT, 2021
** objdump [WSL: Ubuntu]
** File description:
** objdump
*/

#include <sys/mman.h>
#include <stddef.h>
#include <stdio.h>
#include "objdump.h"

bool check_size(Elf64_Ehdr *ehdr, size_t size)
{
    void *addr = ehdr;
    Elf64_Shdr *shdr = NULL;

    if (size < ehdr->e_shoff + sizeof(Elf64_Shdr) * ehdr->e_shnum)
        return true;
    shdr = addr + ehdr->e_shoff;
    if (size < shdr[ehdr->e_shstrndx].sh_offset)
        return true;
    return false;
}

bool check_size32(Elf32_Ehdr *ehdr, size_t size)
{
    void *addr = ehdr;
    Elf32_Shdr *shdr = NULL;

    if (size < ehdr->e_shoff + sizeof(Elf32_Shdr) * ehdr->e_shnum)
        return true;
    shdr = addr + ehdr->e_shoff;
    if (size < shdr[ehdr->e_shstrndx].sh_offset)
        return true;
    return false;
}

bool objdump_arch(Elf64_Ehdr *header, char *file, size_t size)
{
    print_header(header, file);

    if (header->e_ident[EI_CLASS] == ELFCLASS64)
    {
        if (check_size(header, size))
            return true;
        print_sections(header);
    }
    else
    {
        if (check_size32((Elf32_Ehdr *)header, size))
            return true;
        print_sections32((Elf32_Ehdr *)header);
    }
    return false;
}

bool objdump(char *file)
{
    size_t size;
    char *buffer = buffer_file(file, &size);
    bool result = false;

    if (buffer == NULL)
        return true;
    if (check_header((Elf64_Ehdr *)buffer))
    {
        fprintf(stderr, "objdump: %s: file format not recognized\n", file);
        return true;
    }
    result = objdump_arch((Elf64_Ehdr *)buffer, file, size);
    munmap(buffer, size);
    return result;
}