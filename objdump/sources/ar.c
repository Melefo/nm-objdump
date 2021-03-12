/*
** EPITECH PROJECT, 2021
** objdump [WSL: Ubuntu]
** File description:
** ar
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "objdump.h"

char *get_name(char *filenames, struct ar_hdr *hdr)
{
    char *stop = strchr(hdr->ar_name, '/');

    if (stop == hdr->ar_name)
    {
        if (filenames == NULL)
            return NULL;
        return filenames + atoi(hdr->ar_name + 1);
    }
    return hdr->ar_name;
}

int name_size(char *filenames, struct ar_hdr *hdr)
{
    char *stop = strchr(hdr->ar_name, '/');
    char *pos = NULL;

    if (stop == hdr->ar_name)
    {
        if (filenames == NULL)
            return 0;
        pos = filenames + atoi(hdr->ar_name + 1);
        stop = strchr(pos, '/');
        return stop - pos;
    }
    return stop - hdr->ar_name;
}

char *get_nametab(char *tab, struct ar_hdr *hdr, size_t size)
{
    if (strncmp(hdr->ar_name, "//", 2) == 0)
        return (void *)hdr + size;
    return tab;
}

bool objdump_ar(void *ptr, char *file, size_t size)
{
    size_t hdr_size = sizeof(struct ar_hdr);
    struct ar_hdr *hdr = NULL;
    char *names = NULL;
    size_t elf_size = 0;
    bool end = false;
    bool result = false;

    printf("In archive %s:\n", file);
    for (size_t i = 0; i < size && !end; i += hdr_size + elf_size)
    {
        hdr = ptr + i;
        elf_size = atoi(hdr->ar_size);
        end = strncmp(hdr->ar_fmag, ARFMAG, 2);
        names = get_nametab(names, hdr, hdr_size);
        if (check_header((Elf64_Ehdr *)((void *)hdr + hdr_size)))
            continue;
        printf("\n%.*s", name_size(names, hdr), get_name(names, hdr));
        if (objdump_arch((Elf64_Ehdr *)((void *)hdr + hdr_size), "", elf_size))
            result = true;
    }
    return result;
}