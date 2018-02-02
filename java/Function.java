
public class Function{
	private Section m_section;
	private int m_address;
	private int m_size;
	private String m_name;
	private String m_label;
	private Instruction[] m_instructions;
	private Executable m_executable;
	
	public Function(Executable executable, int address, int size, String name){
		m_executable = executable;
		m_size = size;
		m_address = address;
		m_name = name;
		m_label = "";
		
		m_section = m_execuable.findSection(m_address);
	}
	public Executable executable(){
		return m_executable;
	}
	public int address(){
		return m_address;
	}
	public int size(){
		return m_size;
	}
	public Section section(){
		return m_section;
	}
	public void addInstruction(Instruction instruction){
	}
	public native Instruction(int);
	public String toString(){
		String result = "";
		if(m_section.name == ".text"){
			result = "\t.text";
		}
		else{
			result = "\t.section "+m_secton.name;
		}
		result += "\n\t.globl "+m_name+"\n\t.type"+m_name+", @function\n"+m_name+":\ n";
		/*if(m_label != ""){
			result += m_label;
		}*/
		
		for(Instruction instruction : m_instructions){
			result += instruction.toString();
		}
		
		result += "\t.size "+m_name+", .-"+m_name+"\n";
		return result;
	}
}
