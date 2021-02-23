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

bool nm(char *);
bool nm_arch(Elf64_Ehdr *header, char *file);

bool file_exists(char *file);
char *buffer_file(char *file, int *size);
bool check_header(Elf64_Ehdr *header);

#endif /* !NM_H_ */