#include "executable.h"

int extractFunction(Executable* exe)
{
	t_elf_section* symtab;
	if(elf_get_symtab(exe->elf, &symtab) == -1)
	{
		return -1;
	}
	if(symtab == 0)
	{
		return 0;
	}

	ssize_t syms_number = elf_symtab_get_symnum(exe->elf, symtab);
	if(syms_number == 0)
		return 0;
	
	printf("number of symbols: %i\n", syms_number);

    exe->numberFunction = syms_number;
    exe->functions = malloc(sizeof(Function)*syms_number);

    size_t i;
	for(i = 0;i < syms_number;i++)
	{
		t_elf_sym* sym;
		if(elf_symtab_get_sym(exe->elf, symtab, i, &sym) == -1)
		{
			free(sym);
			return -1;
		}
		const char* name;
        elf_sym_get_name(exe->elf, sym, &name);
        
        Function f = {name, elf_sym_get_value(exe->elf, sym), elf_sym_get_size(exe->elf, sym), 0};
		if(elf_sym_get_value(exe->elf, sym) !=0 & elf_sym_get_size(exe, sym) != 0 & elf_sym_get_info(exe, sym) == 18 & name != "_start" & name != "")
		{
            f.optimizable = 1;
			printf(name);
			printf("\n");
        }
        exe->functions[i] = f;
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

void loadExecutable(Executable* exe, const char* name)
{
    exe->elf = malloc(sizeof(t_elf));
    int ret = elf_load_file(name, exe->elf);
    exe->name = name;
    extractFunction(exe);
    printf("------------------------------\n");
    size_t i;
    for(i = 0;i < exe->numberFunction;i++)
    {
        if(exe->functions[i].optimizable)
            printf("%s\n", exe->functions[i].name);
    }
}
void unloadExecutable(Executable* exe)
{
    free(exe->functions);
    elf_free(exe->elf);
    free(exe->elf);
    exe->numberFunction = 0;
}

t_elf_section* findSections(Executable* exe, const char* name)
{
    size_t i;
    for(i = 0;i < elf_header_get_shnum(exe);i++)
    {
        const char* sname; 
        elf_section_get_name(exe, &exe->elf->sections[i], &sname);
        if(sname == name)
        {
            return &exe->elf->sections[i];
        }
    }

    return 0;
}
t_elf_section* findSectioni(Executable* exe, const int address)
{
    size_t i;
    for(i = 0;i < elf_header_get_shnum(exe->elf);i++)
        if(elf_section_get_offset(exe, &exe->elf->sections[i]) == address)
            return &exe->elf->sections[i];

    return 0;
}
Function* findFunctions(Executable* exe, const char* name)
{
    size_t i;
    for(i = 0;i < exe->numberFunction;i++)
        if(exe->functions[i].name == name)
            return &exe->functions[i];

    return 0;
}
Function* findFunctioni(Executable* exe, const int address)
{
    size_t i;
    for(i = 0;i < exe->numberFunction;i++)
        if(exe->functions[i].address == address)
            return &exe->functions[i];

    return 0;
}