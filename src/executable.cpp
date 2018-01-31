#include "executable.hpp"

Executable(std::string);
~Executable();

void extractFunction();
void saveAt(std::string);

void AddFunctionData();

void findSection(std::string);
void findSection(int);
void findFunction(std::string);
void findFunction(int);