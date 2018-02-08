#include "instruction.h"

char* instructionToString(Instruction* instruction)
{
    char* result = malloc(100);
    sprintf(result, "\t%s %s\n", instruction->mnemonic, instruction->operands);

    /*size_t i;
    for(i = 0;i < instruction->numberOperand;i++)
        sprintf(result, "%s, ", instruction->operands[i]);

    result[strlen(result)-2] = " ";
    result[strlen(result)-1] = "\n";
    sprintf(result, "%s\n", instruction->mnemonic, instruction->operands);*/
    return result;
}
Instruction* nextInstruction(Instruction* instruction)
{
    Instruction* insn = (Instruction*)instruction->next;
    return insn;
}