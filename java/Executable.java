import com.sun.org.apache.bcel.internal.generic.Instruction;
import java.awt.Insets;

public class Executable
{
    private Instruction[] m_instructions;
    private String m_name;

    public Executable(String name)
    {
        this.name = name;
        initBinary(name);
    }
    public native void initBinary(String name);
    public native void saveAt(String file_name);

    public native Instruction findSection(String name);
    public native Instruction findSection(int address);
    public native Instruction findFunction(String name);
    public native Instruction findFunction(int address);

    public Instruction[] instruction(){
        return m_instructions;
    }
    public String name(){
        return m_name;
    }
}