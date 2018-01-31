#include "operand.hpp"
#include "instruction.hpp"
#include "function.hpp"
#include "executable.hpp"

Operand::Operand(cs_x86_op op): m_op(op), m_instruction(NULL), m_label("")
{}

void Operand::setInstruction(Instruction* instruction)
{
    if(instruction != NULL)
        m_instruction = instruction;
}
std::string Operand::toString()
{
    if(m_label != "")
        return m_label;
    
    switch(m_op.type)
    {
        case 2:
            return "$"+m_op.imm;
            break;
        case 1:
            return "%"+cs_reg_name(m_op.reg);
            break;
        case 4:
            return m_op.fp;
        case 3:
            std::string res;
            if(m_op.mem.disp != 0)
            {
                if(cs_reg_name(m_op.base) == "rip")
                {
                    int address = m_instruction->address + m_instruction->size + m_op.mem.disp;
                    bool isFunction = false;
                    for(int i(0);i < m_instruction->function()->executable()->functions.size;i++)
                        if(m_instruction->function()->executable()->functions[i].address == address)
                        {
                            isFunction = true;
                            res = m_instruction->function()->executable()->functions[i].name;
                            printf("The address %i is actualy the function %s", address, res);
                            if(m_instruction->function()->section.name == ".rodata" | m_instruction->function()->section.name == ".data")
                                m_instrucion->function()->executable()->addFunctionData(m_instruction->function()->executable()->functions[i]);
                        }

                    if(!isFunction)
                    {
                        res = ".LC"+m_instruction->function()->executable()->functions_data.size;
                        m_instruction->function()->executable()->addFunctionData(Function(address, 0, res));
                    }
                }
                else
                {
                    res = m_op.mem.disp;
                }
            }

            if(m_op.mem.base != 0 & m_op.mem.index != 0 & m_op.mem.scale != 1)
            {
                res += "(";
                if(m_op.mem.base != 0)
                    res += "%" + cs_reg_name(m_op.mem.base);
                if(m_op.mem.index != 0)
                    res += ", " + cs_reg_name(m_op.mem.index);
                if(m_op.meme.scale != 1)
                    res += ", " + m_op.mem.scale;
                res += ")"
            }
            break;
        default:
            printf("operand type Unknow.");
            break;
    }
}