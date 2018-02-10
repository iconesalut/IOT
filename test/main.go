package main

// #cgo LDFLAGS: -lIOT -lcapstone
// #include "executable.h"
import("C")

func main(){
  var e C.struct_Executable
  C.loadExecutable(&e, C.CString("/home/icone/IOT/test_iot"))
  C.saveAt(&e, C.CString("./src.s"))
  C.unloadExecutable(&e)
}
