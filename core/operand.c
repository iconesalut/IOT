#include "operand.h"
#include "executable.h"

char* operandToString(Operand* operand)
{
	char* result = malloc(30);
	if(operand->label != 0)
		strcpy(result, operand->label);
	else
		switch(operand->op.type)
		{
		case X86_OP_REG:
			sprintf(result, "%c%s", 37, cs_reg_name(handle, operand->op.reg));
			break;
		case X86_OP_IMM:
			sprintf(result, "$%i", operand->op.imm);
			break;
		case X86_OP_FP:
			sprintf(result, "%f", operand->op.fp);
			break;
		case X86_OP_MEM:
			strcpy(result, "");
			if(operand->op.mem.disp != 0)
			{
				if(operand->op.mem.base != 0)
				{
					if(operand->op.mem.base == X86_REG_RIP | operand->op.mem.base == X86_REG_EIP | operand->op.mem.base == X86_REG_IP)
					{
						int addr = operand->instruction->instruction.address + operand->instruction->instruction.size + operand->op.mem.disp;
						int isF = 0;
						size_t n;
						for(n = 0;n < operand->instruction->function->exe->numberFunction;n++)
						{
							if(operand->instruction->function->exe->functions[n].address == addr)
							{
								isF = 1;
								strcpy(result, operand->instruction->function->exe->functions[n].name);
							}
						}

						if(!isF)
						{
							printf("function not found\n");
							sprintf(result, "%i", operand->op.mem.disp);
						}
					}
				}
				else
				{
					sprintf(result, "%i", operand->op.mem.disp);
				}
			}
			strcat(result, "(");
			if(operand->op.mem.base != 0)
			{
				char* c = malloc(2);
				sprintf(c, "%c", 37);
				strcat(result, c);
				free(c);
				strcat(result, cs_reg_name(handle, operand->op.mem.base));
			}
			if(operand->op.mem.index != 0)
			{
				char* c = malloc(4);
				sprintf(c, ", %c", 37);
				strcat(result, c);
				free(c);
				strcat(result, cs_reg_name(handle, operand->op.mem.index));
			}
			if(operand->op.mem.scale != 1)
			{
				char* c = malloc(6);
				if(operand->op.mem.index == 0)
					sprintf(c, ", , %i", operand->op.mem.scale);
				else
					sprintf(c, ", %i", operand->op.mem.scale);
				strcat(result, c);
				free(c);
			}
			strcat(result, ")");
			break;
		}

	return result;
}
