/*
** EPITECH PROJECT, 2021
** nm [WSL: Ubuntu]
** File description:
** list
*/

#include <stdlib.h>
#include <string.h>
#include "nm.h"

node_t *create_node32(Elf32_Sym *symbol, char *strtab)
{
    node_t *node = malloc(sizeof(node_t));

    if (node == NULL)
        return node;
    node->next = NULL;
    node->symbol = (Elf64_Sym *)symbol;
    node->strtab = strtab;
    return node;
}

void cmp_nodes32(node_t *node1, node_t *node2)
{
    Elf32_Sym *sym = (Elf32_Sym *)node1->symbol;
    char *strtab = node1->strtab;
    Elf32_Sym *sym2 = (Elf32_Sym *)node2->symbol;
    char *strtab2 = node2->strtab;

    if (strcmp(&strtab[sym->st_name], &strtab2[sym2->st_name]) <= 0)
        return;
    node1->strtab = strtab2;
    node1->symbol = (Elf64_Sym *)sym2;
    node2->strtab = strtab;
    node2->symbol = (Elf64_Sym *)sym;
}

void sort_list32(node_t *list)
{
    for (node_t *node1 = list; node1 != NULL; node1=node1->next)
        for (node_t *node2 = node1->next; node2 != NULL; node2 = node2->next)
            cmp_nodes32(node1, node2);
}