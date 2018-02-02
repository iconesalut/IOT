public class Instruction{
	private Function m_function;
	private String m_mnemonic;
	private Operand[] m_operands;
	private int m_address;
	private int m_size;
	private int m_type;

	public Instruction(Function function, int address, int size, int type, String mnemonic, Operand[] operands){
		m_function = function;
		m_mnemonic = m_mnemonic;
		m_operands = operands;
		m_address = address;
		m_size = size;
		m_type = type;
	}
	public String toString(){
		String result = m_address.toString() + ":\t" + m_mnemonic + "\t\t";
		for(Operand operand : m_operands){
			result += operand.toString() + ", ";
		}
		result += "\n";
		return result;
	}
}
