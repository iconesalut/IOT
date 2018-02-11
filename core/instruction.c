#include "instruction.h"
#include "executable.h"

int instructionGrp(Instruction* instruction, x86_insn_group grp)
{
    size_t n;
    for(n = 0;n < instruction->instruction.detail->groups_count;n++)
        if(instruction->instruction.detail->groups[n] == grp)
            return 1;

    return 0;
}

void instructionSetup(Instruction* instruction)
{
    instruction->numberOperand = instruction->instruction.detail->x86.op_count;
    instruction->operands = malloc(sizeof(Instruction)*instruction->instruction.detail->x86.op_count);
    size_t i;
    for(i = 0;i < instruction->instruction.detail->x86.op_count;i++)
    {
        Operand op;
        op.op = instruction->instruction.detail->x86.operands[i];
        op.instruction = instruction;
        op.label = 0;
        if(instructionGrp(instruction, X86_GRP_JUMP))
        {
            op.label = malloc(10);
            sprintf(op.label, ".L%x", op.op.imm);
        }
        else if(instructionGrp(instruction, X86_GRP_CALL))
        {
            size_t j;
            for(j = 0;j < instruction->function->exe->numberFunction;j++)
                if(instruction->function->exe->functions[j].address == op.op.imm)
                {
                    op.label = instruction->function->exe->functions[j].name;
                }
        }

        instruction->operands[i] = op;
    }
}
char* instructionToString(Instruction* instruction)
{
    char* result = malloc(100);
    strcpy(result, "");
    if(instruction->label != 0)
    {
        strcat(result, instruction->label);
        strcat(result, ":\n");
    }
    strcat(result, "\t");
    strcat(result, instruction->instruction.mnemonic);
    strcat(result, " ");

    size_t i;
    for(i = 0;i < instruction->numberOperand;i++)
    {
        strcat(result, operandToString(&instruction->operands[i]));
        strcat(result, ", ");
    }

    result[strlen(result)-2] = 10;
    result[strlen(result)-1] = 0;
    result[strlen(result)] = 0;
    return result;
}
