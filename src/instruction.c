#include "instruction.h"

char* instructionToString(Instruction* instruction)
{
    char* result;
    sprintf(result, "%x:\t%s ", instruction->address, instruction->mnemonic);

    size_t i;
    for(i = 0;i < instruction->numberOperand;i++)
        sprintf(result, "%s, ", instruction->operands[i]);

    result[strlen(result)-2] = " ";
    result[strlen(result)-1] = "\n";
    return result;
}