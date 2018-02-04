#include "function.h"
#include "executable.h"

Instruction* findInstruction(Function* function, int address)
{
    Instruction* instruct = function->firstInstruction;;
    while(instruct != 0)
    {
        if(instruct->address == address)
            return instruct;
        
        instruct = nextInstruction(instruct);
    }

    return 0;
}
char* functionToString(Function* function)
{
    Executable* exe = (Executable*)function->exe;
    char* result = "\t.section ";
    char* sec_name;
    elf_section_get_name(exe->elf, function->section, &sec_name);
    strcat(result, sec_name);
    strcat(result, "\n\t.globl ");
    strcat(result, function->name);
    strcat(result, "\n\t.type ");
    strcat(result, function->name);
    strcat(result, ", @function\n");
    strcat(result, function->name);
    strcat(result, ":\n");

    size_t i;
    Instruction* instruct = function->firstInstruction;;
    while(instruct != 0)
    {
        strcat(result, instructionToString(instruct));
        instruct = nextInstruction(instruct);
    }

    
    strcat(result, "\t.size ");
    strcat(result, function->name);
    strcat(result, ", .-\n");
    strcat(result, function->name);
    strcat(result, "\n");

    return result;
}