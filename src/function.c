#include "function.h"

Instruction* findInstruction(Function* function, int address)
{
    size_t i;
    for(i = 0;i < function->numberInstruction;i++)
        if(function->instructions[i].address == address)
            return function;

    return 0;
}
char* functionToString(Function* function)
{
    char* result = "\t.section ";
    char* sec_name;
    elf_section_get_name(function->exe->elf, function->section, &sec_name);
    strcat(result, sec_name);
    strcat(result, "\n\t.globl ");
    strcat(result, function->name);
    strcat(result, "\n\t.type ");
    strcat(result, function->name);
    strcat(result, ", @function\n");
    strcat(result, function->name);
    strcat(result, ":\n");

    size_t i;
    for(i = 0;i < function->numberInstruction;i++)
        strcat(result, instructionToString(&function->instructions[i]));

    
    strcat(result, "\t.size ");
    strcat(result, function->name);
    strcat(result, ", .-\n");
    strcat(result, function->name);
    strcat(result, "\n");

    return result;
}