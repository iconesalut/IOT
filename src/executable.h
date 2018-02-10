#ifndef EXECUTABLE_H
#define EXECUTABLE_H

#include "function.h"

struct Executable
{
    t_elf* elf;
    int numberFunction;
    const char* name;
    Function* functions;
};

void loadExecutable(Executable* exe, const char* name);
void unloadExecutable(Executable* exe);
void saveAt(Executable* exe, char* file_name);

t_elf_section* findSections(Executable* exe, const char* name);
t_elf_section* findSectioni(Executable* exe, const int address);
Function* findFunctions(Executable* exe, const char* name);
Function* findFunctioni(Executable* exe, const int address);

#endif
