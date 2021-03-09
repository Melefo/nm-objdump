/*
** EPITECH PROJECT, 2021
** objdump [WSL: Ubuntu]
** File description:
** tests_header
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "objdump.h"
#include "flags.h"

Test(arch, x64)
{
    cr_assert_str_eq(arch(EM_X86_64), "i386:x86-64");
}

Test(arch, x86)
{
    cr_assert_str_eq(arch(EM_386), "i386");
}

Test(arch, others)
{
    cr_assert_str_eq(arch(EM_ARM), "UNKNOWN!");
}

Test(find_flags, exec)
{
    Elf64_Ehdr ehdr = {
        {0x7F, 'E', 'L', 'F', 2, 1, 1, 0, 0},
        ET_EXEC, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
    };
    size_t flags = find_flags(&ehdr, NULL);

    cr_assert_eq(flags, EXEC_P | D_PAGED);
}

Test(find_flags, dyn)
{
    Elf64_Ehdr ehdr = {
        {0x7F, 'E', 'L', 'F', 2, 1, 1, 0, 0},
        ET_DYN, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
    };
    size_t flags = find_flags(&ehdr, NULL);

    cr_assert_eq(flags, DYNAMIC | D_PAGED);
}

Test(find_flags, rel)
{
    Elf64_Ehdr ehdr = {
        {0x7F, 'E', 'L', 'F', 2, 1, 1, 0, 0},
        ET_REL, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
    };
    size_t flags = find_flags(&ehdr, NULL);

    cr_assert_eq(flags, HAS_RELOC);
}

Test(find_flags, sym)
{
    Elf64_Ehdr ehdr = {
        {0x7F, 'E', 'L', 'F', 2, 1, 1, 0, 0},
        ET_EXEC, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0
    };
    Elf64_Shdr shdr[1] = {
        {0, SHT_SYMTAB, 0, 0, 0, 0, 0, 0, 0, 0}
    };
    size_t flags = find_flags(&ehdr, shdr);

    cr_assert_eq(flags, EXEC_P | D_PAGED | HAS_SYMS);
}

Test(find_flags, no_sym)
{
    Elf64_Ehdr ehdr = {
        {0x7F, 'E', 'L', 'F', 2, 1, 1, 0, 0},
        ET_EXEC, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0
    };
    Elf64_Shdr shdr[1] = {
        {0, SHT_PROGBITS, 0, 0, 0, 0, 0, 0, 0, 0}
    };
    size_t flags = find_flags(&ehdr, shdr);

    cr_assert_eq(flags, EXEC_P | D_PAGED);
}

Test(find_flags32, exec)
{
    Elf32_Ehdr ehdr = {
        {0x7F, 'E', 'L', 'F', 2, 1, 1, 0, 0},
        ET_EXEC, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
    };
    size_t flags = find_flags32(&ehdr, NULL);

    cr_assert_eq(flags, EXEC_P | D_PAGED);
}

Test(find_flags32, dyn)
{
    Elf32_Ehdr ehdr = {
        {0x7F, 'E', 'L', 'F', 2, 1, 1, 0, 0},
        ET_DYN, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
    };
    size_t flags = find_flags32(&ehdr, NULL);

    cr_assert_eq(flags, DYNAMIC | D_PAGED);
}

Test(find_flags32, rel)
{
    Elf32_Ehdr ehdr = {
        {0x7F, 'E', 'L', 'F', 2, 1, 1, 0, 0},
        ET_REL, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
    };
    size_t flags = find_flags32(&ehdr, NULL);

    cr_assert_eq(flags, HAS_RELOC);
}

Test(find_flags32, sym)
{
    Elf32_Ehdr ehdr = {
        {0x7F, 'E', 'L', 'F', 2, 1, 1, 0, 0},
        ET_EXEC, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0
    };
    Elf32_Shdr shdr[1] = {
        {0, SHT_SYMTAB, 0, 0, 0, 0, 0, 0, 0, 0}
    };
    size_t flags = find_flags32(&ehdr, shdr);

    cr_assert_eq(flags, EXEC_P | D_PAGED | HAS_SYMS);
}

Test(find_flags32, no_sym)
{
    Elf32_Ehdr ehdr = {
        {0x7F, 'E', 'L', 'F', 2, 1, 1, 0, 0},
        ET_EXEC, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0
    };
    Elf32_Shdr shdr[1] = {
        {0, SHT_PROGBITS, 0, 0, 0, 0, 0, 0, 0, 0}
    };
    size_t flags = find_flags32(&ehdr, shdr);

    cr_assert_eq(flags, EXEC_P | D_PAGED);
}

Test(print_flags, none, .init = cr_redirect_stdout)
{
    print_flags(0);
    fflush(stdout);

    cr_assert_stdout_eq_str("BFD_NO_FLAGS");
}

Test(print_flags, print, .init = cr_redirect_stdout)
{
    print_flags(EXEC_P | D_PAGED);
    fflush(stdout);

    cr_assert_stdout_eq_str("EXEC_P, D_PAGED");
}

Test(find_flags, class64, .init = cr_redirect_stdout)
{
    Elf64_Ehdr ehdr = {
        {0x7F, 'E', 'L', 'F', ELFCLASS64, 1, 1, 0, 0},
        ET_EXEC, EM_X86_64, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0
    };

    print_header(&ehdr, "HelloWorld");
    fflush(stdout);

    cr_assert_stdout_neq_str("");
}

Test(find_flags, class32, .init = cr_redirect_stdout)
{
    Elf64_Ehdr ehdr = {
        {0x7F, 'E', 'L', 'F', ELFCLASS32, 1, 1, 0, 0},
        ET_EXEC, EM_386, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0
    };

    print_header(&ehdr, "HelloWorld");
    fflush(stdout);

    cr_assert_stdout_neq_str("");
}