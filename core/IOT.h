/*************************************************************************************//**
 *  @file       IOT.h
 *
 *  @brief      Brief description of IOT.h
 *
 *  @date       2018-02-09 08:30
 *         
 **************************************************************************************/


#ifndef IOT_H
#define IOT_H

#include "Elfparse/elfparse.h"
#include <capstone/capstone.h>
#include <capstone/x86.h>
#include <string.h>

csh handle;
int _count;
cs_insn* _insn;

typedef struct Operand Operand;
typedef struct Instruction Instruction;
typedef struct Function Function;
typedef struct Executable Executable;

#endif /* !IOT_H */

