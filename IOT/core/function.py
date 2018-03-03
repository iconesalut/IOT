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
                print(ins.__str__(), end="")
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
                str = "\t.section " + self.section.name
            str = str + "\n\t.globl " + self.name + "\n\t.type " + self.name + ", @function\n" + self.name + ":\n"
        if self.label:
            str = self.name + ":\n"

        for ins in self.instructions:
            str = str + ins.__str__()

        str = str + "\t.size " + self.name + ", .-" + self.name + "\n"

        return str