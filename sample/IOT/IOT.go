package IOT

// #cgo LDFLAGS: -lIOT -lcapstone
// #include "../../core/executable.h"
import("C")

type Executable struct{
	native C.struct_Executable 
}
func (exe *Executable) Load(file string) int{
	C.loadExecutable(&exe.native, C.CString(file))
	return 0
}
func (exe *Executable) SaveAt(file string) int{
	C.saveAt(&exe.native, C.CString(file))
	return 0
}
func (exe *Executable) Unload() int{
	C.unloadExecutable(&exe.native)
	return 0
}
type Function C.struct_Function
type Instruction C.struct_Instruction
type Operand C.struct_Operand