#include "executable.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
	const char* filename = argv[1];
	printf(filename);
	printf("\n");
	Executable exe;
	loadExecutable(&exe, filename);

	//disassembly executable
	/*csh handle;
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
	}*/
	unloadExecutable(&exe);
}