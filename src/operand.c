#include "operand.h"

char* operandToString(Operand* operand)
{
  char* result;// = malloc(30);
  /*switch(operand->type)
  {
    case 1:
      //strcpy(result, operand->reg);
    */  result = operand->reg;
    /*  break;
    case 2:
      //sprintf(result, "%i", operand->imm);
      break;
    case 3:
      //sprintf(result, "%f", operand->fp);
      break;
    case 4:
      //strcpy(result, "");
      break;
  }
 */ return result;
}
