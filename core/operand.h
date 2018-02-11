#ifndef OPERAND_H
#define OPERAND_H

#include "IOT.h"

struct Operand
{
	cs_x86_op op;
	char* label;
	Instruction* instruction;
};

char* operandToString(Operand* operand);

#endif
