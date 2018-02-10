package main

// #include "executable.h"
import("C")
import("fmt")

func main(){
  e := C.Executable();
  C.loadExecutable(e);
  fmt.Println(C.saveAt(e, "src.s"));
  C.unloadExecutable(e);
}
