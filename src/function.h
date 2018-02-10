#ifndef FUNCTION_H
#define FUNCTION_H

#include "instruction.h"

struct Function
{
    char* name;
    int numberInstruction;
    Instruction* firstInstruction;
    void* exe;
    t_elf_section* section;
    int address;
    int size;
    int optimizable;
};

Instruction* findInstruction(Function* function, int address);
char* functionToString(Function* function);

#endif
