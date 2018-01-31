#ifndef INSTRUCTION_HPP
#define INSTRUCTION_HPP

#include "operand.hpp"

class Function;
class Instruction
{
public:
    Instruction(int,int,std::string,std::vector<Operand>,int);
    void setFunction(Function*);
    Function* function();
    int address();
    int size();
	std::string toString();
private:
	int m_address;
    int m_size;
    Function* m_function;
    std::vector<Operand> m_operands;
    std::string m_label;
	std::string m_mnemonic;
	char m_type;
};
#endif