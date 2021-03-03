/*
** EPITECH PROJECT, 2021
** objdump [WSL: Ubuntu]
** File description:
** tests_objdump
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "objdump.h"

Test(objdump, okey64)
{
    cr_assert(!objdump("unit_tests"));
}

Test(objdump, okey32)
{
    cr_assert(!objdump("tests/fsnotifier"));
}

Test(objdump, wrong, .init = cr_redirect_stderr)
{
    cr_assert(objdump("Makefile"));
    cr_assert_stderr_eq_str("objdump: Makefile: file format not recognized\n");
}

Test(objdump, corrupted)
{
    cr_assert(objdump("tests/corrupted"));
}