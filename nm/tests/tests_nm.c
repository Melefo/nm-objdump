/*
** EPITECH PROJECT, 2021
** nm [WSL: Ubuntu]
** File description:
** tests_nm
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "nm.h"

Test(nm, okey)
{
    cr_assert(!nm("unit_tests"));
}

Test(nm, wrong, .init = cr_redirect_stderr)
{
    cr_assert(nm("Makefile"));
    cr_assert_stderr_eq_str("nm: Makefile: file format not recognized\n");
}