#ifndef __ELF_H_
#define __ELF_H_

#include <stdint.h>

typedef enum _ELF_IDENT
{
    EI_MAG0 = 0,
    EI_MAG1 = 1,
    EI_MAG2 = 2,
    EI_MAG3 = 3,
    EI_CLASS = 4,
    EI_DATA = 5,
    EI_VERSION = 6,
    EI_OSABI = 7,
    EI_ABIVERSION = 8
} ELF_IDENT;

typedef enum _ELF_PT
{
    PT_NULL = 0,
    PT_LOAD = 1,
    PT_DYNAMIC = 2,
    PT_INTERP = 3,
    PT_NOTE = 4,
    PT_SHLIB = 5,
    PT_PHDR = 6,
    PT_TLS = 7
} ELF_PT;

/* 32-bit ELF image header structure */
typedef struct _ELF32_HEADER
{
    /* NOTE: EI_NIDENT seems to always be defined as 16. */
    uint8_t e_ident[16];
    uint16_t e_type;
    uint16_t e_machine;
    uint32_t e_version;
    uint32_t e_entry;
    uint32_t e_phoff;
    uint32_t e_shoff;
    uint32_t e_flags;
    uint16_t e_ehsize;
    uint16_t e_phentsize;
    uint16_t e_phnum;
    uint16_t e_shentsize;
    uint16_t e_shnum;
    uint16_t e_shstrndx;
} ELF32_HEADER, *PELF32_HEADER;

/* 64-bit ELF image header structure */
typedef struct _ELF64_HEADER
{
    /* NOTE: EI_NIDENT seems to always be defined as 16. */
    uint8_t e_ident[16];
    uint16_t e_type;
    uint16_t e_machine;
    uint32_t e_version;
    uint64_t e_entry;
    uint64_t e_phoff;
    uint64_t e_shoff;
    uint32_t e_flags;
    uint16_t e_ehsize;
    uint16_t e_phentsize;
    uint16_t e_phnum;
    uint16_t e_shentsize;
    uint16_t e_shnum;
    uint16_t e_shstrndx;
} ELF64_HEADER, *PELF64_HEADER;

/* 32-bit ELF program header structure */
typedef struct _ELF32_PROGRAM_HEADER
{
    uint32_t p_type;
    uint32_t p_offset;
    uint32_t p_vaddr;
    uint32_t p_paddr;
    uint32_t p_filesz;
    uint32_t p_memsz;
    uint32_t p_flags;
    uint32_t p_align;
} ELF32_PROGRAM_HEADER, *PELF32_PROGRAM_HEADER;

/* 64-bit ELF program header structure */
typedef struct _ELF64_PROGRAM_HEADER
{
    uint32_t p_type;
    uint32_t p_flags;
    uint64_t p_offset;
    uint64_t p_vaddr;
    uint64_t p_paddr;
    uint64_t p_filesz;
    uint64_t p_memsz;
    uint64_t p_align;
} ELF64_PROGRAM_HEADER, *PELF64_PROGRAM_HEADER;

/* ELF image representation structure */
typedef struct _ELF_IMAGE_CONTEXT
{
    union
    {
        PELF32_HEADER Header32;
        PELF64_HEADER Header64;
    };
    void *Data;
    uint64_t FileSize;
    uint32_t ImagePages;
    uint32_t ImageSize;
    void *PhysicalAddress;
    void *VirtualAddress;
} ELF_IMAGE_CONTEXT, *PELF_IMAGE_CONTEXT;

#endif /* __ELF_H_ */