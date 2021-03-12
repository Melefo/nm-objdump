/*
** EPITECH PROJECT, 2021
** objdump [WSL: Ubuntu]
** File description:
** objdump
*/

#ifndef OBJDUMP_H_
#define OBJDUMP_H_

#include <stdbool.h>
#include <stddef.h>
#include <elf.h>
#include <ar.h>

bool objdump(char *file);
bool objdump_arch(Elf64_Ehdr *header, char *file, size_t size);

bool file_exists(char *file);
char *buffer_file(char *file, size_t *size);
bool check_header(Elf64_Ehdr *header);

void print_header(Elf64_Ehdr *header, char *file);
char *arch(Elf64_Half machine);
size_t find_flags(Elf64_Ehdr *ehdr, Elf64_Shdr *shdr);
size_t find_flags32(Elf32_Ehdr *ehdr, Elf32_Shdr *shdr);
void print_flags(size_t flag);

void print_sections(Elf64_Ehdr *header);
void print_sections32(Elf32_Ehdr *header);

bool objdump_ar(void *ptr, char *file, size_t size);

#endif /* !OBJDUMP_H_ */
