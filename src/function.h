#ifndef FUNCTION_H
#define FUNCTION_H

#include "instruction.h"
#include "executable.h"

typedef struct
{
    char* name;
    int numberInstruction;
    Instruction* instructions;
    Executable* exe;
    t_elf_section* section;
    int address;
    int size;
    int optimizable;
}Function;

Instruction* findInstruction(Function* function, int address);
char* functionToString(Function* function);

#endif