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

bool print_error(char *file, char *error, bool result)
{
    fprintf(stderr, "nm: %s: %s\n", file, error);
    return result;
}

bool nm_32(Elf32_Ehdr *ehdr, char *file, size_t size)
{
    void *addr = ehdr;
    Elf32_Shdr *shdr = NULL;
    char *shstrtab = NULL;
    node_t *list = NULL;

    if (check_size32(ehdr, &shdr, &shstrtab, size))
        return print_error(file, "file format not recognized", true);
    if (ehdr->e_shstrndx == SHN_UNDEF)
        return print_error(file, "no symbols", false);
    for (int i = 0; i < ehdr->e_shnum; i++)
    {
        if (strcmp(shstrtab + shdr[i].sh_name, ".strtab"))
            continue;
        append_node(&list, extract_symbols32(ehdr, addr + shdr[i].sh_offset));
    }
    sort_list32(list);
    print_symbols32(list, ehdr);
    if (list == NULL)
        return print_error(file, "no symbols", false);
    return false;
}

bool nm_64(Elf64_Ehdr *ehdr, char *file, size_t size)
{
    void *addr = ehdr;
    Elf64_Shdr *shdr = NULL;
    char *shstrtab = NULL;
    node_t *list = NULL;

    if (check_size(ehdr, &shdr, &shstrtab, size))
        return print_error(file, "file format not recognized", true);
    if (ehdr->e_shstrndx == SHN_UNDEF)
        return print_error(file, "no symbols", false);
    for (int i = 0; i < ehdr->e_shnum; i++)
    {
        if (strcmp(shstrtab + shdr[i].sh_name, ".strtab"))
            continue;
        append_node(&list, extract_symbols(ehdr, addr + shdr[i].sh_offset));
    }
    sort_list(list);
    print_symbols(list, ehdr);
    if (list == NULL)
        return print_error(file, "no symbols", false);
    return false;
}

bool nm_arch(Elf64_Ehdr *header, char *file, size_t size)
{
    if (header->e_ident[EI_CLASS] == ELFCLASS64)
        return nm_64(header, file, size);
    return nm_32((Elf32_Ehdr *)header, file, size);
}

bool nm(char *file)
{
    size_t size;
    char *buffer = buffer_file(file, &size);
    bool result = false;

    if (buffer == NULL)
        return true;
    if (check_header((Elf64_Ehdr *)buffer))
    {
        fprintf(stderr, "nm: %s: file format not recognized\n", file);
        return true;
    }
    result = nm_arch((Elf64_Ehdr *)buffer, file, size);
    munmap(buffer, size);
    return result;
}