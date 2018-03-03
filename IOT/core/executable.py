from filebytes.elf import *
from capstone import *
from capstone.x86 import *
from IOT.core.function import *
from IOT.core.instruction import *
from IOT.core.operand import *


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
        src_file = open(file_src, "w")

        #        src_file.write(self.print_datasection(self.find_section(".rodata")))
        #        src_file.write(self.print_datasection(self.find_section(".data")))
        #        src_file.write(self.print_datasection(self.find_section(".bss")))

        print("print the functions ")
        for i, function in enumerate(self.functions_optimazable):
            for ins in function.instructions:
                ins.setup()
            function.setup()
            print((i + 1) / len(self.functions_optimazable) * 100, "%\t(", function.name, ")")
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
                print(function.name, function.address, l + data.header.sh_offset)
                if l + data.header.sh_offset == function.address:
                    src_file.write(function.name + ":\n")

            src_file.write(".byte " + byte.__str__() + "\n")

        src_file.close()

        os.system("gcc " + file_src + " -o " + file_name)

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
            self.functions.append(Function(plt_addr, entsize, symbol_name + "@PLT", self))

        if dynsym_section:
            for symbol in dynsym_section.symbols:
                if (symbol.header.st_value != 0 or symbol.header.st_size != 0):
                    self.functions.append(Function(symbol.header.st_value, symbol.header.st_size, symbol.name, self))

        symtab_section = self.find_section(".symtab")
        if symtab_section:
            for symbol in symtab_section.symbols:
                self.functions.append(Function(symbol.header.st_value, symbol.header.st_size, symbol.name, self))

        for i, f in enumerate(self.functions):
            if (f.name[:2] == "_Z" or f.name != "" and f.name[:1] != '_') and f.name[len(
                    f.name) - 4:] != "@PLT" and f.address != 0 and f.size > 2 and f.section == self.text:
                self.functions_optimazable.append(f)
                print(f.name, f.size)