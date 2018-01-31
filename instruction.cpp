#include "instruction.hpp"

Instruction::Instruction(int address,int size,std::string mnemonic,std::vector<Operand> operands): m_address(address), m_size(size), m_mnemonic(mnemonic), m_operands(operands), m_type(-1)
{
    for(int i(0);i < m_operands.size();i++)
    {
        m_operands[i].setInstruction(this);
    }

    m_label = ".L" + m_address;
}
void Instruction::setFunction(Function* function)
{
    if(function != 0)
        m_function = function;
}
Function* Instruction::function()
{
    return m_function;
}
int Instruction::address()
{
    return m_address;
}
int Instruction::size()
{
    return m_size;
}
std::string Instruction::toString()
{
    std::string res = m_label + ":\t" + m_mnemonic + "\t\t";
    for(int i(0);i < m_operands.size();i++)
        res += m_operands[i].toString() + ", ";
    
    res.substr(0, res.size()-2);
    res += "\n";

    return res;
}