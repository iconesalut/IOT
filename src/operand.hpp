#ifndef OPERAND_HPP
#define OPERAND_HPP

#include <string>
#include <vector>
#include <map>
#include <capstone/capstone.h>

class Instruction;
class Operand
{
public:
	Operand(cs_x86_op);
    ~Operand();
    void setInstruction(Instruction*);
	std::string toString();
private:
    std::string m_label;
    Instruction* m_instruction;
	cs_x86_op m_op;
};
#endif