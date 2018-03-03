from IOT.core.function import *

class Operand():
    def __init__(self, op):
        self.op = op
        self.label = ""
    def __str__(self):
        if self.label != "":
            return self.label
        elif self.op.type == 2:
            return "$"+self.op.value.imm.__str__()
        elif self.op.type == 1:
            return "%"+self.instruction.insn.reg_name(self.op.value.reg)
        elif self.op.type == 4:
            return self.op.value.fp.__str__()
        elif self.op.type == 3:
            str = ""
            if self.op.value.mem.disp != 0:
                str = self.op.value.mem.disp.__str__()
#                if self.instruction.insn.reg_name(self.op.value.mem.base) == "rip":
                addr = self.instruction.address + self.instruction.size + self.op.value.mem.disp
                isF=False
                for function in self.instruction.function.executable.functions:
                    if function.address == addr:
                        isF=True
                        str = function.name
                        print("The address of this memory", addr, "at ", function.name)
                        if function.section.name == ".rodata" or function.section.name == ".data":
                            function.executable.functions_data.append(function)
                if not isF:
                    name = ".LC"+(len(self.instruction.function.executable.functions_data)+1).__str__()
                    self.instruction.function.executable.functions_data.append(Function(addr, 0, name,self.instruction.function.executable))
                    str = name
            str = str + "("
            if self.op.value.mem.base != 0:
                str = str + "%" + self.instruction.insn.reg_name(self.op.value.mem.base)
            if self.op.value.mem.index != 0:
                str = str + ", %" + self.instruction.insn.reg_name(self.op.value.mem.index)
            if self.op.value.mem.scale != 1:
                str = str + ", " + self.op.value.mem.scale.__str__()
            str = str + ")"
            return str
        if self.op.type == 0:
            return "Error type"
        else:
            print(self.instruction.op_str())