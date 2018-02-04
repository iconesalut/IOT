#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include "Elfparse/elfparse.h"
#include <string.h>
#include "function.h"

typedef struct
{
    int address;
    int size;
    Function* function;
    char* mnemonic;
    int numberOperand;
    char** operands;
}Instruction;

char* instructionToString(Instruction* instruction);

#endif