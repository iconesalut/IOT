#ifndef EXECUTABLE_HPP
#define EXECUTABLE_HPP

#include <inttypes.h>
#include <LIEF/LIEF.hpp>
#include "function.hpp"

class Executable
{
public:
	Executable(std::string);
    ~Executable();
	void extractFunction();
    void saveAt(std::string);
    
    void AddFunctionData();

	void findSection(std::string);
	void findSection(int);
	void findFunction(std::string);
	void findFunction(int);
private:
	Elf_Binary_t* m_binary;
	std::vector<Function> functions, functions_data, function_optimizable;
};
#endif