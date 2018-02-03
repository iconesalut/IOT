public class Executable
{
    private Function[] m_functions;
    private Section[] m_sections;
    private String m_name;

    public Executable(String name)
    {
        this.name = name;
        initBinary(name);

        for(Function function : m_functions){
            System.out.print(function.name);
        }
    }
    public native void initBinary(String name);
    public native void saveAt(String file_name);

    public native Section findSection(String name);
    public native Section findSection(int address);
    public native Function findFunction(String name);
    public native Function findFunction(int address);

    public Function[] function(){
        return m_functions;
    }
    public Section[] sections(){
        return m_sections;
    }
    public String name(){
        return m_name;
    }
}