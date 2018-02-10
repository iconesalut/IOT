#include "executable.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
	const char* filename = argv[1];
	printf(filename);
	printf("\n");
	Executable exe;
	loadExecutable(&exe, filename);
  saveAt(&exe, strcat(filename, "_src.s"));
	unloadExecutable(&exe);
}
