#ifndef OPERAND_H
#define OPERAND_H

#include "IOT.h"

struct Operand
{
  int address;
  int size;
  int type;
  char* reg;
  int imm;
  float fp;  
  struct
  {
    int disp; 
    char* index;
    char* base;
    int scale; 
  };
};

char* operandToString(Operand* operand);

#endif
