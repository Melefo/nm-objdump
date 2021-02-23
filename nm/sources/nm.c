/*
** EPITECH PROJECT, 2021
** B-PSU-400-NAN-4-1-nmobjdump-victor.trencic [WSL: Ubuntu]
** File description:
** nm
*/

#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
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
    return true;
}

bool nm(char *file)
{
    return false;
}