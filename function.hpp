#ifndef FUNCTION_HPP
#define FUNCTION_HPP

#include "instruction.hpp"
#include <LIEF/LIEF.hpp>

class Executable;
class Function
{
public:
	Function(int,int,std::string);
    ~Function();
    void setExecutable(Executable*);
    Executable* executable();
    LIEF::ELF::Section& section();
    void addInstruction(Instruction);
	Instruction findInstruction(int);
	std::string toString();
private:
	std::string m_name;
	int m_address;
    int m_size;
    std::map<int, Instruction> m_instructions;
    Executable* m_executable;
    LIEF::ELF::Section& m_section;
	bool m_is_static;
    bool m_is_imported;
};
#endif