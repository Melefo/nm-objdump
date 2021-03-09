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

char *arch(Elf64_Half machine)
{
    if (machine == EM_X86_64)
        return "i386:x86-64";
    if (machine == EM_386)
        return "i386";
    return "UNKNOWN!";
}

size_t find_flags(Elf64_Ehdr *ehdr, Elf64_Shdr *shdr)
{
    size_t flag = 0;

    if (ehdr->e_type == ET_EXEC)
        flag |= EXEC_P | D_PAGED;
    if (ehdr->e_type == ET_DYN)
        flag |= DYNAMIC | D_PAGED;
    if (ehdr->e_type == ET_REL)
        flag |= HAS_RELOC;
    for (int i = 0; i < ehdr->e_shnum; i++)
    {
        if (shdr[i].sh_type == SHT_SYMTAB)
            flag |= HAS_SYMS;
    }
    return (flag);
}

size_t find_flags32(Elf32_Ehdr *ehdr, Elf32_Shdr *shdr)
{
    size_t flag = 0;

    if (ehdr->e_type == ET_EXEC)
        flag |= EXEC_P | D_PAGED;
    if (ehdr->e_type == ET_DYN)
        flag |= DYNAMIC | D_PAGED;
    if (ehdr->e_type == ET_REL)
        flag |= HAS_RELOC;
    for (int i = 0; i < ehdr->e_shnum; i++)
    {
        if (shdr[i].sh_type == SHT_SYMTAB)
            flag |= HAS_SYMS;
    }
    return (flag);
}

void print_flags(size_t flag)
{
    char *separator = "";

    if (flag == flags[0].flag)
    {
        printf("%s", flags[0].str);
        return;
    }
    for (int i = 1; flags[i].str != NULL; i++)
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
    Elf32_Ehdr *ehdr32 = (Elf32_Ehdr *)ehdr;
    size_t flag = 0;

    printf("%s:     ", file);
    if (ehdr->e_ident[EI_CLASS] == ELFCLASS64)
    {
        flag = find_flags(ehdr, (void *)ehdr + ehdr->e_shoff);
        printf("file format elf64-x86-64\n");
    }
    else
    {
        flag = find_flags32(ehdr32, (void *)ehdr32 + ehdr32->e_shoff);
        printf("file format elf32-i386\n");
    }
    printf("architecture: %s, flags 0x%08lx:\n", arch(ehdr->e_machine), flag);
    print_flags(flag);
    if (ehdr->e_ident[EI_CLASS] == ELFCLASS64)
        printf("\nstart address 0x%016lx\n\n", ehdr->e_entry);
    else
        printf("\nstart address 0x%08x\n\n", ehdr32->e_entry);
}