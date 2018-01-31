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
	std::unique_ptr<const LIEF::ELF::Binary> m_binary;
	std::vector<Function> m_functions, m_functionsData, m_functionOptimizable;
};
#endif