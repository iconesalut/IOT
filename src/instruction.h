#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include "Elfparse/elfparse.h"
#include <capstone/capstone.h>
#include <capstone/x86.h>
#include <string.h>

typedef struct
{
    int address;
    int size;
    void* function;
    char* mnemonic;
    int numberOperand;
    char* operands;
    void* next;
}Instruction;

char* instructionToString(Instruction* instruction);
Instruction* nextInstruction(Instruction* instruction);

#endif