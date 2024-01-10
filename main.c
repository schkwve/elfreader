#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#include "elf.h"

void validate_elf_file(FILE *file, char *buffer)
{
	PELF32_HEADER Header32 = (PELF32_HEADER)buffer;
	PELF64_HEADER Header64 = (PELF64_HEADER)buffer;

	if(Header32->e_ident[EI_MAG0] != 0x7F ||
       Header32->e_ident[EI_MAG1] != 0x45 ||
       Header32->e_ident[EI_MAG2] != 0x4C ||
       Header32->e_ident[EI_MAG3] != 0x46)
    {
        /* ELF file header is invalid */
		printf("[!] File is not a valid ELF file!\n");
        exit(-4);
    }

    /* Check architecture */
    if(Header32->e_ident[EI_CLASS] == 1)
    {
        /* 32-bit executable */
		printf("[ ] 32-bit executable\n");
		printf("[ ] Entry point: 0x%x\n", Header32->e_entry);
		printf("[ ] Program header offset: 0x%x\n", Header32->e_phoff);
		printf("[ ] Section header offset: 0x%x\n", Header32->e_shoff);
		printf("[ ] Program header count: 0x%hx\n", Header32->e_phnum);
		printf("[ ] Section header count: 0x%hx\n", Header32->e_shnum);
		PELF32_PROGRAM_HEADER program_headers = (PELF32_PROGRAM_HEADER)(buffer + Header32->e_phoff);

		for (int i = 0; i < Header32->e_phnum; i++) {
			printf("Program header %d:", i);
			printf("\t[ ] Type: 0x%x\n", program_headers[i].p_type);
			printf("\t[ ] Offset: 0x%x\n", program_headers[i].p_offset);
			printf("\t[ ] Physical address: 0x%x\n", program_headers[i].p_paddr);
			printf("\t[ ] Virtual address: 0x%x\n", program_headers[i].p_vaddr);
			printf("\t[ ] Filesize: 0x%x\n", program_headers[i].p_filesz);
			printf("\t[ ] Memory Size: 0x%x\n", program_headers[i].p_memsz);
			printf("\t[ ] Flags: 0x%x\n", program_headers[i].p_flags);
			printf("\t[ ] Align: 0x%x\n", program_headers[i].p_align);
		}
    }
    else if(Header32->e_ident[EI_CLASS] == 2)
    {
        /* 64-bit executable */
		printf("[ ] 64-bit executable\n");
		printf("[ ] Entry point: 0x%llx\n", Header64->e_entry);
		printf("[ ] Program header offset: 0x%llx\n", Header64->e_phoff);
		printf("[ ] Section header offset: 0x%llx\n", Header64->e_shoff);
		printf("[ ] Program header count: 0x%hx\n", Header64->e_phnum);
		printf("[ ] Section header count: 0x%hx\n", Header64->e_shnum);

		PELF64_PROGRAM_HEADER program_headers = (PELF64_PROGRAM_HEADER)(buffer + Header64->e_phoff);
		for (int i = 0; i < Header64->e_phnum; i++) {
			printf("Program header %d:\n", i);
			printf("\t[ ] Type: 0x%x\n", program_headers[i].p_type);
			printf("\t[ ] Offset: 0x%llx\n", program_headers[i].p_offset);
			printf("\t[ ] Physical address: 0x%llx\n", program_headers[i].p_paddr);
			printf("\t[ ] Virtual address: 0x%llx\n", program_headers[i].p_vaddr);
			printf("\t[ ] Filesize: 0x%llx\n", program_headers[i].p_filesz);
			printf("\t[ ] Memory Size: 0x%llx\n", program_headers[i].p_memsz);
			printf("\t[ ] Flags: 0x%x\n", program_headers[i].p_flags);
			printf("\t[ ] Align: 0x%llx\n", program_headers[i].p_align);
		}
    }
    else
    {
        /* Invalid executable */
		printf("[!] Invalid architecture!\n");
        exit(-5);
    }

    /* Check endianness */
    if(Header32->e_ident[EI_DATA] != 1)
    {
        /* Big-endian */
		printf("[ ] Endianness: Big endian\n");
    }
	else
	{
		/* Little-endian */
		printf("[ ] Endianness: Little endian\n");
	}

	/* Subsystem */
	printf("[ ] Subsystem: ");
	switch(Header32->e_ident[EI_OSABI])
	{
		case 0x00:
			printf("System V");
			break;
		case 0x01:
			printf("HP-UX");
			break;
		case 0x02:
			printf("NetBSD");
			break;
		case 0x03:
			printf("Linux");
			break;
		case 0x04:
			printf("GNU Hurd");
			break;
		case 0x06:
			printf("Solaris");
			break;
		case 0x07:
			printf("AIX");
			break;
		case 0x08:
			printf("IRIX");
			break;
		case 0x09:
			printf("FreeBSD");
			break;
		case 0x0A:
			printf("Tru64");
			break;
		case 0x0B:
			printf("Novell Modesto");
			break;
		case 0x0C:
			printf("OpenBSD");
			break;
		case 0x0D:
			printf("OpenVMS");
			break;
		case 0x0E:
			printf("NonStop Kernel");
			break;
		case 0x0F:
			printf("AROS");
			break;
		case 0x10:
			printf("FenixOS");
			break;
		case 0x11:
			printf("Nuxi CloudABI");
			break;
		case 0x12:
			printf("Stratus Technologies OpenVOS");
			break;
		default:
			printf("Unknown");
			break;
	}
	printf("\n");

	/* Filetype */
	printf("[ ] File type: ");
	switch(Header32->e_type)
	{
		case 0x00:
			printf("None");
			break;
		case 0x01:
			printf("Relocatable");
			break;
		case 0x02:
			printf("Executable");
			break;
		case 0x03:
			printf("Dynamic");
			break;
		default:
			printf("Unknown");
			break;
	}
	printf("\n");

	/* Machine type */
	printf("[ ] Target: ");
	switch(Header32->e_machine)
	{
		case 0x00:
			printf("No specific ISA");
			break;
		case 0x02:
			printf("SPARC");
			break;
		case 0x03:
			printf("x86");
			break;
		case 0x08:
			printf("MIPS");
			break;
		case 0x14:
			printf("PowerPC");
			break;
		case 0x16:
			printf("S390");
			break;
		case 0x28:
			printf("ARM");
			break;
		case 0x2A:
			printf("SuperH");
			break;
		case 0x32:
			printf("IA-64");
			break;
		case 0x3E:
			printf("x86-64");
			break;
		case 0xB7:
			printf("AArch64");
			break;
		case 0xF3:
			printf("RISC-V");
			break;
		default:
			printf("Unknown");
			break;
	}
	printf("\n");
}

int main(int argc, char *argv[])
{
	if (argc <= 1) {
		printf("[!] No filename supplied!\n");
		return -1;
	}

	FILE *file;
	size_t filesize = 0;

	/* Open file */
	file = fopen(argv[1], "rb");
	if (file == NULL) {
		printf("[!] Unable to open file %s: %s\n", argv[1], strerror(errno));
		return -2;
	}

	/* Get filesize */
	fseek(file, 0, SEEK_END);
	filesize = ftell(file);
	rewind(file);

	printf("[*] Size: %zu bytes\n", filesize);

	/* Allocate a buffer for the entire file */
	char *filebuf = malloc(filesize + 1);

	/* Read file into the buffer */
	fread(filebuf, filesize, 1, file);

	validate_elf_file(file, filebuf);

	fclose(file);
	free(filebuf);

	return 0;
}