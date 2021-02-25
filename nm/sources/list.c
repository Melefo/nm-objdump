/*
** EPITECH PROJECT, 2021
** nm [WSL: Ubuntu]
** File description:
** list
*/

#include <stdlib.h>
#include <string.h>
#include "nm.h"

void append_node(node_t **list, node_t *node)
{
    node_t *tmp = *list;

    if (*list == NULL)
    {
        *list = node;
        return;
    }
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = node;
}

node_t *create_node(Elf64_Sym *symbol, char *strtab)
{
    node_t *node = malloc(sizeof(node_t));

    if (node == NULL)
        return node;
    node->next = NULL;
    node->symbol = symbol;
    node->strtab = strtab;
    return node;
}

size_t size_list(node_t *list)
{
    size_t size = 0;

    while (list)
    {
        size++;
        list = list->next;
    }
    return size;
}

void cmp_nodes(node_t *node1, node_t *node2)
{
    Elf64_Sym *sym = node1->symbol;
    char *strtab = node1->strtab;
    Elf64_Sym *sym2 = node2->symbol;
    char *strtab2 = node2->strtab;

    if (strcmp(&strtab[sym->st_name], &strtab2[sym2->st_name]) <= 0)
        return;
    node1->strtab = strtab2;
    node1->symbol = sym2;
    node2->strtab = strtab;
    node2->symbol = sym;
}

void sort_list(node_t *list)
{
    for (node_t *node1 = list; node1 != NULL; node1=node1->next)
        for (node_t *node2 = node1->next; node2 != NULL; node2 = node2->next)
            cmp_nodes(node1, node2);
}