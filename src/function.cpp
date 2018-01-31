#include "function.hpp"
#include <algorithm>

class AddressSort
{
public:
    bool operator()(const Instruction a1, const int Instruction a2)
    {
        return a1.address < a2.address;
    }
};

Function::Function(int address,int size,std::string name): m_address(address), m_size(size), m_name(name), m_executable(NULL)
{}
void Function::setExecutable(Executable* executable)
{
    if(executable != NULL)
    {
        m_executable = executable;
        for(LIEF::ELF::Section& section : m_executable->sections())
        {
            if(m_address > section.offset & m_address < section.offset + section.size)
                m_section = section;
        }
    }
}
Executable* Function::executable()
{
    return m_executable;
}
LIEF::ELF::Section& Function::section()
{
    return m_section;
}
void Function::addInstruction(Instruction instruction)
{
    m_instructions[instruction.address()] = instruction;
}
Instruction Function::findInstruction(int address)
{
    return m_instructions[address];
}
std::string Function::toString()
{
    sort(m_instructions.begin(), m_instructions.end(), AddressSort());

    std::string res;
    if(m_section.name == ".text")
        res = "\t.text";
    else
        res = "\t.section "+m_section.name;
    
    res += "\n\t.globl " + m_name + "\n\t.type " + m_name + ", @sunction\n" + m_name + ":\n";
    for(std::map<Instruction>::iterator it(m_instructions.begin());it != m_instructions.end();++it)
    {
        res += it->toString();
    }

    res += "\t.size " + m_name + ", .-" + m_name + "\n";
    return res;
}