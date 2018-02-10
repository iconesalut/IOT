#include "instruction.h"

char* instructionToString(Instruction* instruction)
{
    char* result = malloc(strlen(instruction->mnemonic)+instruction->numberOperand+4);
    sprintf(result, "\t%s \n", instruction->mnemonic);
  
    size_t i;
/*    for(i = 0;i < instruction->numberOperand;i++)
    {
        strcat(result, operandToString(&instruction->operands[i]));
    }

    result[strlen(result)-2] = "\0";
    result[strlen(result)-1] = 0;
    result[strlen(result)] = 0;*/
    //sprintf(result, "%s\n", instruction->mnemonic);// , instruction->operands);
    return result;
}
Instruction* nextInstruction(Instruction* instruction)
{
    Instruction* insn = (Instruction*)instruction->next;
    return insn;
}
