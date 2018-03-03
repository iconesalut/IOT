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