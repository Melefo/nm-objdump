/*
** EPITECH PROJECT, 2021
** B-PSU-400-NAN-4-1-nmobjdump-victor.trencic [WSL: Ubuntu]
** File description:
** nm
*/

#ifndef NM_H_
#define NM_H_

#include <stddef.h>
#include <stdbool.h>
#include <elf.h>
#include <ar.h>

typedef struct node {
    Elf64_Sym *symbol;
    char *strtab;
    struct node *next;
} node_t;

typedef struct type {
    char c;
    Elf64_Word type;
    Elf64_Xword flags;
} type_t;

bool nm(char *);
bool nm_arch(Elf64_Ehdr *header, char *file, size_t size);

bool file_exists(char *file);
char *buffer_file(char *file, size_t *size);
bool check_header(Elf64_Ehdr *header);

node_t *extract_symbols(Elf64_Ehdr *header, char *strtab);
void print_symbols(node_t *list, Elf64_Ehdr *elf);

node_t *extract_symbols32(Elf32_Ehdr *header, char *strtab);
void print_symbols32(node_t *list, Elf32_Ehdr *elf);

void append_node(node_t **list, node_t *node);
node_t *create_node(Elf64_Sym *symbol, char *strtab);
void sort_list(node_t *list);
size_t size_list(node_t *list);

node_t *create_node32(Elf32_Sym *symbol, char *strtab);
void sort_list32(node_t *list);

bool check_size(Elf64_Ehdr *ehdr, Elf64_Shdr **shdr, char **tab, size_t);
bool check_size32(Elf32_Ehdr *ehdr, Elf32_Shdr **shdr, char **tab, size_t);

bool nm_ar(void *ptr, char *file, size_t size);

#endif /* !NM_H_ */