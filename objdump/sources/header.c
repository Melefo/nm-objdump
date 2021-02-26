/*
** EPITECH PROJECT, 2021
** objdump [WSL: Ubuntu]
** File description:
** header
*/

#include <stdio.h>
#include "objdump.h"
#include "flags.h"

static flag_t flags[] = {
    {"BFD_NO_FLAGS", BFD_NO_FLAGS},
    {"HAS_RELOC", HAS_RELOC},
    {"EXEC_P", EXEC_P},
    {"HAS_LINENO", HAS_LINENO},
    {"HAS_DEBUG", HAS_DEBUG},
    {"HAS_SYMS", HAS_SYMS},
    {"HAS_LOCALS", HAS_LOCALS},
    {"DYNAMIC", DYNAMIC},
    {"WP_TEXT", WP_TEXT},
    {"D_PAGED", D_PAGED},
    {NULL, 0}
};

char *str_arch(Elf64_Ehdr *header)
{
    switch (header->e_machine)
    {
    case EM_X86_64:
        return "i386:x86-64";
    case EM_386:
        return "i386";
    default:
        return "UNKNOWN!";
    }
}

void print_flags(Elf64_Word flag)
{
    char *separator = "";

    for (int i = 0; flags[i].str != NULL; i++)
    {
        if (flag & flags[i].flag)
        {
            printf("%s%s", separator, flags[i].str);
            separator = ", ";
        }
    }
}

void print_header(Elf64_Ehdr *ehdr, char *file)
{
    printf("%s:     ", file);
    if (ehdr->e_ident[EI_CLASS] == ELFCLASS64)
        printf("file format elf64-x86-64\n");
    else
        printf("file format elf32-i386\n");
    printf("architecture: %s, flags 0x%08x:\n", str_arch(ehdr), ehdr->e_flags);
    print_flags(ehdr->e_flags);
    printf("\nstart address 0x%016lx\n\n", ehdr->e_entry);
}