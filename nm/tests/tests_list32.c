/*
** EPITECH PROJECT, 2021
** nm [WSL: Ubuntu]
** File description:
** tests_list32
*/

#include <criterion/criterion.h>
#include "nm.h"

Test(create_node32, create)
{
    Elf32_Sym sym = {};
    Elf32_Sym *sym_ptr = &sym;
    char *str = "Hello World";

    node_t *node = create_node32(sym_ptr, str);

    cr_assert_not_null(node);
    cr_assert_eq(node->symbol, sym_ptr);
    cr_assert_eq(node->strtab, str);
    cr_assert_null(node->next);
}

Test(sort_cmp32, sorted)
{
    Elf32_Sym sym = {0, 0, 0, 0, 0, 0};
    Elf32_Sym *sym_ptr = &sym;
    char *str = "Hello World";
    char *str2 = "Bye World";
    char *str3 = "Welcome back World";

    node_t *list = NULL;
    node_t *node = create_node32(sym_ptr, str);
    node_t *node2 = create_node32(sym_ptr, str2);
    node_t *node3 = create_node32(sym_ptr, str3);

    append_node(&list, node);
    append_node(&list, node2);
    append_node(&list, node3);
    sort_list32(list);

    cr_assert_eq(list->strtab, str2);
    cr_assert_eq(list->next->strtab, str);
    cr_assert_eq(list->next->next->strtab, str3);
}