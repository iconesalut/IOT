package main

import "os"
import "fmt"
import "./IOT"


func main(){
	if len(os.Args) > 2{
		var exe IOT.Executable
		exe.Load(os.Args[1])
		exe.SaveAt(os.Args[2])
		exe.Unload()
	}else{
		fmt.Println( os.Args[0], "[input] [output]")
	}
}
