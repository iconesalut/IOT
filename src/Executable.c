#include "Executable.h"
#include "Elfparse/elfparse.h"
#include <stdio.h>
#include <stdlib.h>

JNIEXPORT void JNICALL Java_Executable_initBinary(JNIEnv *env, jobject obj, jstring name)
{
	const char* filename = (*env)->GetStringUTFChars(env, name, 0);
	printf(filename);
	printf("\n");
	t_elf exe;
	int ret = elf_load_file(filename, &exe);
	size_t i;
	for(i = 0;i < elf_header_get_shnum(&exe);i++)
	{
		const char* name;
		if(elf_section_get_name(&exe,&exe.sections[i],&name) != -1)
		{
			printf(name);
			printf("\n");
		}
	}
	elf_free(&exe);
	(*env)->ReleaseStringUTFChars(env, name, filename);
}
JNIEXPORT void JNICALL Java_Executable_saveAt(JNIEnv *env, jobject obj, jstring name)
{}
JNIEXPORT void JNICALL Java_Executable_findSection__Ljava_lang_String_2(JNIEnv *env, jobject obj, jstring name)
{}
JNIEXPORT void JNICALL Java_Executable_findSection__I(JNIEnv *env, jobject obj, jint address)
{}
JNIEXPORT void JNICALL Java_Executable_findFunction__Ljava_lang_String_2(JNIEnv *env, jobject obj, jstring name)
{}
JNIEXPORT void JNICALL Java_Executable_findFunction__I(JNIEnv *env, jobject obj, jint address)
{}
