public class Executable
{
    public Executable(String name)
    {
        this.name = name;
        initBinary(name);
    }
    public native void initBinary(String name);
    public native void saveAt(String file_name);

    public native void findSection(String name);
    public native void findSection(int address);
    public native void findFunction(String name);
    public native void findFunction(int address);

    private String name;
}