/*
** EPITECH PROJECT, 2021
** nm [WSL: Ubuntu]
** File description:
** handler
*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include "nm.h"

bool file_exists(char *file)
{
    struct stat file_stat;

    if (stat(file, &file_stat) == -1)
    {
        fprintf(stderr, "nm: '%s': No such file\n", file);
        return false;
    }
    if (!S_ISREG(file_stat.st_mode))
    {
        fprintf(stderr, "nm: Warning: '%s' is a directory\n", file);
        return false;
    }
    return file_stat.st_size > 0;
}

char *buffer_file(char *file, size_t *size)
{
    int fd = open(file, O_RDONLY);
    struct stat file_stat;
    char *buffer;

    if (fd == -1)
        return NULL;
    if (fstat(fd, &file_stat) == -1)
        return NULL;
    buffer = mmap(NULL, file_stat.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
    close(fd);
    if (buffer == (void *)-1)
        return NULL;
    *size = file_stat.st_size;
    return buffer;
}

bool check_header(Elf64_Ehdr *header)
{
    if (header->e_ident[EI_MAG0] != ELFMAG0 \
    || header->e_ident[EI_MAG1] != ELFMAG1 \
    || header->e_ident[EI_MAG2] != ELFMAG2 \
    || header->e_ident[EI_MAG3] != ELFMAG3)
        return true;
    if (header->e_ident[EI_CLASS] != ELFCLASS64 \
    && header->e_ident[EI_CLASS] != ELFCLASS32)
        return true;
    if (header->e_ident[EI_DATA] != ELFDATA2LSB \
    && header->e_ident[EI_DATA] != ELFDATA2MSB)
        return true;
    if (header->e_ident[EI_VERSION] != EV_CURRENT)
        return true;
    return false;
}
