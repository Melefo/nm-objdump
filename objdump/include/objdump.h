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

bool objdump(char *file);

bool file_exists(char *file);
char *buffer_file(char *file, int *size);
bool check_header(Elf64_Ehdr *header);

void print_header(Elf64_Ehdr *header, char *file);

void print_sections(Elf64_Ehdr *header);

#endif /* !OBJDUMP_H_ */
