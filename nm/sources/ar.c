/*
** EPITECH PROJECT, 2021
** B-PSU-400-NAN-4-1-nmobjdump-victor.trencic [WSL: Ubuntu]
** File description:
** ar
*/

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "nm.h"

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

bool nm_ar(void *ptr, char *file, size_t size)
{
    size_t hdr_size = sizeof(struct ar_hdr);
    struct ar_hdr *hdr = NULL;
    char *names = NULL;
    size_t elf_size = 0;
    bool end = false;
    bool result = false;

    for (size_t i = 0; i < size && !end; i += hdr_size + elf_size)
    {
        hdr = ptr + i;
        elf_size = atoi(hdr->ar_size);
        end = strncmp(hdr->ar_fmag, ARFMAG, 2);
        if (strncmp(hdr->ar_name, "//", 2) == 0)
            names = (void *)hdr + hdr_size;
        if (check_header((Elf64_Ehdr *)((void *)hdr + hdr_size)))
            continue;
        printf("\n%.*s:\n", name_size(names, hdr), get_name(names, hdr));
        if (nm_arch((Elf64_Ehdr *)((void *)hdr + hdr_size), file, elf_size))
            result = true;
    }
    return result;
}