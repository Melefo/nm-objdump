/*
** EPITECH PROJECT, 2021
** objdump [WSL: Ubuntu]
** File description:
** objdump
*/

#ifndef OBJDUMP_H_
#define OBJDUMP_H_

#include <stdbool.h>
#include <elf.h>

typedef struct header {
    unsigned char *e_ident;
    Elf64_Half	e_machine;
    Elf64_Word	e_flags;
    Elf64_Addr	e_entry;
} header_t;

bool objdump(char *file);

bool file_exists(char *file);
char *buffer_file(char *file, int *size);
bool check_header(Elf64_Ehdr *header);

void print_header(header_t header, char *file);

void print_sections(Elf64_Ehdr *header);
void print_sections32(Elf32_Ehdr *header);

#endif /* !OBJDUMP_H_ */
