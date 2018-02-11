#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include "operand.h"

struct Instruction
{
    cs_insn instruction;
    int numberOperand;
    Operand* operands;
    char* label;
    Function* function;
    Instruction* next;
};

void instructionSetup(Instruction* instruction);
char* instructionToString(Instruction* instruction);

#endif