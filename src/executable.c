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
        
        Function f = {name, 0, 0, exe, findSectioni(exe, elf_sym_get_value(exe->elf, sym)), elf_sym_get_value(exe->elf, sym), elf_sym_get_size(exe->elf, sym), 0};
		if(elf_sym_get_value(exe->elf, sym) !=0 & elf_sym_get_size(exe, sym) != 0 & elf_sym_get_info(exe, sym) == 18 & (strcmp(name, "_start") | !strcmp(name, "main")) & name != "")
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
int disassembly(Executable* exe)
{
    csh handle;
    cs_open(CS_ARCH_X86, CS_MODE_64, &handle);
    cs_option(handle, CS_OPT_SYNTAX, CS_OPT_SYNTAX_ATT);

    size_t i;
    for(i = 0;i < elf_header_get_shnum(exe->elf);i++)
    {
        const char* name;
        if(elf_section_get_name(exe->elf, &exe->elf->sections[i], &name) != -1)
        {
            printf("%s\n", name);
            if(!strcmp(name, ".text"))
            {
                cs_insn* insn;
                size_t count;
                count = cs_disasm(handle, exe->elf->sections[i].content, elf_section_get_size(exe->elf, &exe->elf->sections[i]), elf_section_get_offset(exe->elf, &exe->elf->sections[i]), 0, &insn);
                if(count)
                {
                    size_t j;
                    for(j = 0;j < count;j++)
                    {
                        Function* f = findFunctioni(exe, insn[j].address);
                        if(f != 0)
                            if(f->optimizable)
                            {
                                f->numberInstruction++;
                                Instruction* instruction_ptr = malloc(sizeof(Instruction));
                                instruction_ptr->address = insn[j].address;
                                instruction_ptr->size = insn[j].size;
                                instruction_ptr->function = f;
                                instruction_ptr->mnemonic = insn[j].mnemonic;
                                instruction_ptr->operands = insn[j].op_str;
                                instruction_ptr->next = 0;//(void*)f->firstInstruction;
                                if(f->firstInstruction != 0)
                                {
                                    Instruction* last = f->firstInstruction;
                                    while(last->next != 0)
                                    {
                                        last = nextInstruction(last);
                                    }
                                    last->next = (void*)instruction_ptr;
                                }
                                else
                                {
                                  f->firstInstruction = instruction_ptr;
                                }
                                //f->firstInstruction = instruction_ptr;
                            }
                    }
                }
            }
        }
    }
    return 0;
}

void loadExecutable(Executable* exe, const char* name)
{
    exe->elf = malloc(sizeof(t_elf));
    int ret = elf_load_file(name, exe->elf);
    exe->name = name;
    printf("---------------extract the function---------------------\n");
    extractFunction(exe);
    printf("-------------disassembly the exexutable-----------------\n");
    disassembly(exe);
}
void saveAt(Executable* exe, char* file_name)
{
    printf("-----------------create a new file----------------------\n");
    FILE* src = fopen(file_name, "w");
    if(src == NULL)
      exit(-1);
    printf("-----------------write in the file----------------------\n");
    size_t i;
    for(i = 0;i < exe->numberFunction;i++)
    {
        if(exe->functions[i].optimizable)
        {
            Instruction* instruct = exe->functions[i].firstInstruction;
            printf("%s\n", exe->functions[i].name);
            if(exe->functions[i].optimizable)
            {
                char* str = functionToString(&exe->functions[i]);
                printf("%s", str);
                fprintf(src, "%s", str);
//                free(str);
            }
        }
    }
    fclose(src);
}
void unloadExecutable(Executable* exe)
{
    size_t i;
    for(i = 0;i < exe->numberFunction;i++)
        while(exe->functions[i].firstInstruction != 0)
        {
            void* insn = exe->functions[i].firstInstruction;
            Instruction* instruction = (Instruction*)exe->functions[i].firstInstruction;
            exe->functions[i].firstInstruction = instruction->next;
            free(insn);
        }

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
        if(elf_section_get_offset(exe, &exe->elf->sections[i]) < address & elf_section_get_offset(exe, &exe->elf->sections[i]) + elf_section_get_size(exe, &exe->elf->sections[i]) > address)
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
        if(exe->functions[i].address <= address && exe->functions[i].address + exe->functions[i].size > address)
            return &exe->functions[i];

    return 0;
}
