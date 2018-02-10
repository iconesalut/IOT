#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include "operand.h"

struct Instruction
{
    int address;
    int size;
    void* function;
    char* mnemonic;
    int numberOperand;
    Operand* operands;
    void* next;
};

char* instructionToString(Instruction* instruction);
Instruction* nextInstruction(Instruction* instruction);

#endif
