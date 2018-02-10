#!/usr/bin/python3
from capstone import *
from capstone.x86 import *
from filebytes.elf import *
import argparse
import os

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

class Instruction():
    CALL = 0
    JUMP = 1
    def __init__(self, insn, operands, function):
        self.function = function
        self.insn = insn
        self.address = insn.address
        self.size  = insn.size
        self.type = -1
        self.mnemonic = insn.mnemonic
        self.operands = operands
        for op in self.operands:
            op.instruction = self
        self.label = ".L" + hex(self.address)

    def setup(self):
        for operand in self.operands:
            if self.mnemonic[0] == 'j' and self.operands[0].label == "":# or self.mnemonic[:4] == "call":
                self.operands[0].label = ".L" + hex(self.operands[0].op.imm)
            else:
                if self.mnemonic[:4] == "call":
                    for f in self.function.executable.functions:
                        if f.address == self.operands[0].op.imm:
                            self.operands[0].label = f.name

    def __str__(self):
        str = ""
        if self.label != "":
            str = self.label + ":"
        str = str + "\t"+self.mnemonic+"\t\t"
        for operand in self.operands:
            str = str + operand.__str__() + ", "

        str = str[0:len(str)-2] + "\n"
        return str

class Function():
    def __init__(self, address, size, name, exe):
        self.address = address
        self.section = exe.find_sectiona(address)
        self.name = name
        self.size = size
        self.type = type
        self.label = False
        self.executable = exe
        self.instructions = []

    def setup(self):
        for ins in self.instructions:
#                if ins.mnemonic[:3] == "lea":
#                    print(ins.__str__(), ins.operands[0].op.mem.disp + ins.address + 7)
            if ins.mnemonic[:4] == "call":
                print(ins.__str__(),end="")
                for function in self.executable.functions:
                    if function.address == ins.operands[0].op.imm:
                        print("it's the function", function.name)
                        ins.operands[0].label = function.name

    def find_instruction(self, address):
        for instruction in self.instructions:
            if instruction.address == address:
                return instruction

        return 0

    def __str__(self):

        if self.section.name is not int:
            if self.section.name == ".text":
                str = "\t.text"
            else:
                str = "\t.section "+self.section.name
            str = str+"\n\t.globl "+self.name+"\n\t.type "+self.name+", @function\n"+self.name+":\n"
        if self.label:
            str = self.name+":\n"
            
        for ins in self.instructions:
            str = str + ins.__str__()

        str = str+"\t.size "+self.name+", .-"+self.name+"\n"

        return str

class Executable():
    def __init__(self, file_name):
        self.file_name = file_name
        self.exe = ELF(self.file_name)
        self.functions = []
        self.functions_optimazable = []
        self.functions_data = []
        self.text = self.find_section(".text")

        self.extract_function()

        dis = Cs(CS_ARCH_X86, CS_MODE_64)
        dis.syntax = CS_OPT_SYNTAX_ATT
        dis.detail = True
        for section in self.exe.sections:
            if section.name != ".rodata" and section.name != ".data" and section.name != ".bss":
                for i, insn in enumerate(dis.disasm(section.bytes, section.header.sh_offset)):
                    for function in self.functions:
                        if function.address <= insn.address and function.address + function.size > insn.address:
                            operands = []
                            for i, op in enumerate(insn.operands):
                                operands.append(Operand(op))
                            function.instructions.append(Instruction(insn, operands, function))

    def save_at(self, file_name):
        file_src = file_name + "_src.s"
        src_file = open(file_src,"w")

#        src_file.write(self.print_datasection(self.find_section(".rodata")))
#        src_file.write(self.print_datasection(self.find_section(".data")))
#        src_file.write(self.print_datasection(self.find_section(".bss")))

        print("print the functions ")
        for i, function in enumerate(self.functions_optimazable):
            for ins in function.instructions:
                ins.setup()
            function.setup()
            print((i+1)/len(self.functions_optimazable)*100,"%\t(",function.name,")")
            src_file.write(function.__str__())

#        for i, function in enumerate(self.functions_data):
#            for f in self.functions_data:
#                if function.address  f.address:
#                    f_tmp = f
#                    self.functions_data.remove(f)
#                    self.functions_data.insert(i, 

        data = self.find_section(".rodata")
        src_file.write("\t.section .rodata\n")
        for l, byte in enumerate(data.bytes):
            for i, function in enumerate(self.functions_data):
                print(function.name, function.address, l+data.header.sh_offset)
                if l+data.header.sh_offset == function.address:
                    src_file.write(function.name+":\n")

            src_file.write(".byte "+byte.__str__()+"\n")

        src_file.close()

        os.system("gcc "+file_src+" -o "+file_name)

    def find_section(self, section_name):
        for section in self.exe.sections:
            if section.name == section_name:
                return section

        return 0
    def find_sectiona(self, address):
        for section in self.exe.sections:
            if address > section.header.sh_offset and address < section.header.sh_offset + section.header.sh_size:
                return section
        
        return 0

    def find_function(self, address):
        for function in self.functions:
            if address >= function.address and address <= function.address + function.size:
                return function

        return 0
    def find_functionn(self, name):
        for function in self.functions:
            if name == function.name:
                return function

        return 0

    def extract_function(self):
        reloc_section = self.find_section(".rela.plt")
        dynsym_section = self.find_section(".dynsym")
        plt_section = self.find_section(".plt")
        for id, reloc in enumerate(reloc_section.relocations):
            symbol_name = reloc.symbol.name
            entsize = plt_section.header.sh_size / (len(reloc_section.relocations) + 1)
            plt_addr = plt_section.header.sh_addr + ((id + 1) * entsize)
            self.functions.append(Function(plt_addr, entsize,symbol_name+"@PLT",self))

        if dynsym_section:
            for symbol in dynsym_section.symbols:
                if(symbol.header.st_value != 0 or symbol.header.st_size != 0):
                    self.functions.append(Function(symbol.header.st_value, symbol.header.st_size,symbol.name,self))

        symtab_section = self.find_section(".symtab")
        if symtab_section:
            for symbol in symtab_section.symbols:
                self.functions.append(Function(symbol.header.st_value, symbol.header.st_size,symbol.name,self))

        for i, f in enumerate(self.functions):
            if (f.name[:2] == "_Z" or f.name != "" and f.name[:1] != '_') and f.name[len(f.name)-4:] != "@PLT" and f.address != 0 and f.size > 2 and f.section == self.text:
                self.functions_optimazable.append(f)
                print(f.name,f.size)

if __name__ == '__main__':
    parse = argparse.ArgumentParser()
    parse.add_argument("file_input", help="the file that you want optimize")
    parse.add_argument("file_output", help="the file that we create")
    args = parse.parse_args()
    exe = Executable(args.file_input)
    exe.save_at(args.file_output)
