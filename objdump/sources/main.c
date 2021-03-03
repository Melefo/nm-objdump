/*
** EPITECH PROJECT, 2021
** B-PSU-400-NAN-4-1-nmobjdump-victor.trencic [WSL: Ubuntu]
** File description:
** main
*/

#include <stdio.h>
#include "objdump.h"

bool multiple_files(int argc, char **argv)
{
    bool error = false;

    for (int i = 1; i < argc; i++)
    {
        if (!file_exists(argv[i]))
        {
            error = true;
            continue;
        }
        printf("\n");
        if (objdump(argv[i]))
            error = true;
    }
    return error;
}

bool one_file(char *file)
{
    if (!file_exists(file))
        return 1;
    return objdump(file);
}

int main(int argc, char **argv)
{
    if (argc == 1)
        return one_file("a.out");
    if (argc == 2)
        return one_file(argv[1]);
    return multiple_files(argc, argv);
}