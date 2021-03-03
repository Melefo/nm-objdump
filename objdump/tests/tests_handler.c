/*
** EPITECH PROJECT, 2021
** objdump [WSL: Ubuntu]
** File description:
** tests_handler
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "objdump.h"

Test(file_exists, true)
{
    cr_assert(file_exists("tests/tests_handler.c"));
}

Test(file_exists, false, .init = cr_redirect_stderr)
{
    cr_assert(!file_exists("tests/unknown"));
    cr_assert_stderr_eq_str("nm: 'tests/unknown': No such file\n");
}

Test(file_exists, directory, .init = cr_redirect_stderr)
{
    cr_assert(!file_exists("tests/"));
    cr_assert_stderr_eq_str("nm: Warning: 'tests/' is a directory\n");
}

Test(buffer_file, map)
{
    size_t size = 0;

    cr_assert_not_null(buffer_file("tests/tests_handler.c", &size));
    cr_assert(size > 0);
}

Test(buffer_file, fd)
{
    size_t size = 0;

    cr_assert_null(buffer_file("test", &size));
    cr_assert_eq(size, 0);
}

Test(check_header, correct)
{
    Elf64_Ehdr ehdr = {
        {0x7F, 'E', 'L', 'F', 2, 1, 1, 0, 0},
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
    };

    cr_assert(!check_header(&ehdr));
}

Test(check_header, magic)
{
    Elf64_Ehdr ehdr = {
        {0x7F, 'N', 'O', 'P', 2, 1, 1, 0, 0},
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
    };

    cr_assert(check_header(&ehdr));
}

Test(check_header, class)
{
    Elf64_Ehdr ehdr = {
        {0x7F, 'E', 'L', 'F', 0, 1, 1, 0, 0},
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
    };

    cr_assert(check_header(&ehdr));
}

Test(check_header, data)
{
    Elf64_Ehdr ehdr = {
        {0x7F, 'E', 'L', 'F', 2, 0, 1, 0, 0},
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
    };

    cr_assert(check_header(&ehdr));
}

Test(check_header, version)
{
    Elf64_Ehdr ehdr = {
        {0x7F, 'E', 'L', 'F', 2, 1, 0, 0, 0},
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
    };

    cr_assert(check_header(&ehdr));
}

Test(check_header, abi)
{
    Elf64_Ehdr ehdr = {
        {0x7F, 'E', 'L', 'F', 2, 1, 1, 0, 1},
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
    };

    cr_assert(check_header(&ehdr));
}