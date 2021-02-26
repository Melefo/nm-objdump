/*
** EPITECH PROJECT, 2021
** objdump [WSL: Ubuntu]
** File description:
** handler
*/

#include <sys/stat.h>
#include <stdio.h>
#include "objdump.h"

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
