#include "executable.hpp"

Executable::Executable(std::string file_name)
{}
Executable::~Executable()
{}

void Executable::extractFunction()
{}
void Executable::saveAt(std::string)
{}

void Executable::AddFunctionData()
{}

void Executable::findSection(std::string name)
{}
void Executable::findSection(int address)
{}
void Executable::findFunction(std::string name)
{}
void Executable::findFunction(int address)
{}