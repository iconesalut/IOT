#include "Elfparse/elfparse.h"
#include "function.h"

typedef struct
{
    t_elf* elf;
    int numberFunction;
    const char* name;
    Function* functions;
}Executable;

void loadExecutable(Executable* exe, const char* name);
void unloadExecutable(Executable* exe);

t_elf_section* findSections(Executable* exe, const char* name);
t_elf_section* findSectioni(Executable* exe, const int address);
Function* findFunctions(Executable* exe, const char* name);
Function* findFunctioni(Executable* exe, const int address);