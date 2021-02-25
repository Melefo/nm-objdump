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

bool nm_64(Elf64_Ehdr *ehdr, char *file)
{
    void *addr = ehdr;
    Elf64_Shdr *shdr = addr + ehdr->e_shoff;
    char *shstrtab = addr + shdr[ehdr->e_shstrndx].sh_offset;
    node_t *list = NULL;

    if (ehdr->e_shstrndx == SHN_UNDEF)
    {
        fprintf(stdout, "nm: %s: no symbols\n", file);
        return false;
    }
    for (int i = 0; i < ehdr->e_shnum; i++)
    {
        if (strcmp(shstrtab + shdr[i].sh_name, ".strtab"))
            continue;
        append_node(&list, extract_symbols(ehdr, addr + shdr[i].sh_offset));
    }
    sort_list(list);
    print_symbols(list, ehdr);
    return list == NULL;
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