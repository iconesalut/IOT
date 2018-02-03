#include "Elfparse/elfparse.h"
#include <capstone/capstone.h>
#include <capstone/x86.h>
#include <stdio.h>
#include <stdlib.h>

int extractFunction(t_elf* exe)
{
	t_elf_section* symtab;
	if(elf_get_symtab(exe, &symtab) == -1)
	{
		return -1;
	}
	if(symtab == NULL)
	{
		return 0;
	}

	ssize_t syms_number = elf_symtab_get_symnum(exe, symtab);
	if(syms_number == NULL)
		return 0;
	
	printf("number of symbols: %i\n", syms_number);
/*
	if(syms = malloc((syms_number+1)*sizeof(t_elf_sym *)) == NULL)
	{
		printf("error allocation memory!");
		return -1;
	}*/
	size_t i;
	for(i = 0;i < syms_number;i++)
	{/*
		if(syms[i] = malloc(sizeof(t_sym)) == NULL)
		{
			printf("error allocation memory!!");
			return -1;
		}*/
		t_elf_sym* sym;
		if(elf_symtab_get_sym(exe, symtab, i, &sym) == -1)
		{
			free(sym);
			return -1;
		}
		const char* name;
		elf_sym_get_name(exe, sym, &name);
		if(elf_sym_get_value(exe, sym) !=0 & elf_sym_get_size(exe, sym) != 0 & elf_sym_get_info(exe, sym) == 18 & name != "")
		{
			printf(name);
			printf("\t-> adress: %i\tsize: %i\n", elf_sym_get_value(exe, sym), elf_sym_get_size(exe, sym));
		}
	}
	/*i = 0;
	while(syms[i])
	{
		printf(syms[i]->name);
		printf("\n");
		i++;
	}*/

	return 0;
}

int main(int argc, char** argv)
{
	const char* filename = argv[1];
	printf(filename);
	printf("\n");

	//disassembly executable
	csh handle;
	cs_open(CS_ARCH_X86,CS_MODE_64,&handle);
	cs_option(handle,CS_OPT_SYNTAX,CS_OPT_SYNTAX_ATT);
	t_elf exe;
	int ret = elf_load_file(filename, &exe);
	extractFunction(&exe);

	size_t i;
	for(i = 0;i < elf_header_get_shnum(&exe);i++)
	{
		const char* name;
		if(elf_section_get_name(&exe,&exe.sections[i],&name) != -1)
		{
			if(name != ".rodata" & name != ".bss" & name !=".data")
			{
				printf(name);
				printf("\n");
				cs_insn* insn;
				size_t count;
				count = cs_disasm(handle, exe.sections[i].content, elf_section_get_size(&exe, &exe.sections[i]), elf_section_get_offset(&exe, &exe.sections[i]), 0, &insn);
				if(count)
				{
					size_t j;
					for(j = 0;j < count;j++)
					{
						printf("\t%s\t%s\n", insn[j].mnemonic, insn[j].op_str);
					}
				}
			}
		}
	}
	elf_free(&exe);
}