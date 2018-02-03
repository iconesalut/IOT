#include "Executable.h"
#include "Elfparse/elfparse.h"
#include <capstone/capstone.h>
#include <capstone/x86.h>
#include <stdio.h>
#include <stdlib.h>

int extractFunction(t_elf* exe)
{
	t_elf_section* symtab;
	if(elf_get_symtab(exe, &symtab) == -1)
	{
		return -1;
	}
	if(symtab == NULL)
	{
		return 0;
	}

	ssize_t syms_number = elf_symtab_get_symnum(exe, symtab);
	if(syms_number == NULL)
		return 0;
	
	printf("number of symbols: %i\n", syms_number);
/*
	if(syms = malloc((syms_number+1)*sizeof(t_elf_sym *)) == NULL)
	{
		printf("error allocation memory!");
		return -1;
	}*/
	size_t i;
	for(i = 0;i < syms_number;i++)
	{/*
		if(syms[i] = malloc(sizeof(t_sym)) == NULL)
		{
			printf("error allocation memory!!");
			return -1;
		}*/
		t_elf_sym* sym;
		if(elf_symtab_get_sym(exe, symtab, i, &sym) == -1)
		{
			free(sym);
			return -1;
		}
		const char* name;
		elf_sym_get_name(exe, sym, &name);
		if(elf_sym_get_value(exe, sym) !=0 & elf_sym_get_size(exe, sym) != 0 & elf_sym_get_info(exe, sym) == 18 & name != "")
		{
			printf(name);
			printf("\t-> adress: %i\tsize: %i\n", elf_sym_get_value(exe, sym), elf_sym_get_size(exe, sym));
		}
	}
	/*i = 0;
	while(syms[i])
	{
		printf(syms[i]->name);
		printf("\n");
		i++;
	}*/

	return 0;
}

JNIEXPORT void JNICALL Java_Executable_initBinary(JNIEnv *env, jobject obj, jstring name)
{
	const char* filename = (*env)->GetStringUTFChars(env, name, 0);
	jclass function = (*env)->FindClass(env, "Function");
	jfieldID functionID = (*env)->GetFieldID(env, function, "m_functions", "[LFunction");
	jmethodID functionConstructor = (*env)->GetMethodID(env, function, "<init>", "(LExecutable;IILjava/lang/String;)V");
	jobject functions = (*env)->GetObjectField(env, obj, functionID);
	printf(filename);
	printf("\n");

	//load elf file
	t_elf exe;
	int ret = elf_load_file(filename, &exe);
	extractFunction(&exe);

	//extract function
	t_elf_section* symtab;
	if(elf_get_symtab(&exe, &symtab) == -1)
	{
		exit(-1);
	}
	if(symtab == NULL)
	{
		exit(-1);
	}

	ssize_t syms_number = elf_symtab_get_symnum(&exe, symtab);
	if(syms_number == NULL)
		exit(-1);	
	printf("number of symbols: %i\n", syms_number);

	jobjectArray functionArray = (*env)->NewObjectArray(env, (jsize)syms_number, function, functions);
	size_t i;
	for(i = 0;i < syms_number;i++)
	{
		t_elf_sym* sym;
		if(elf_symtab_get_sym(&exe, symtab, i, &sym) == -1)
		{
			free(sym);
			exit(-1);
		}
		const char* name;
		elf_sym_get_name(&exe, sym, &name);
		if(elf_sym_get_value(&exe, sym) !=0 & elf_sym_get_size(&exe, sym) != 0 & elf_sym_get_info(&exe, sym) == 18 & name != "")
		{
			printf(name);
			printf("\t-> adress: %i\tsize: %i\n", elf_sym_get_value(&exe, sym), elf_sym_get_size(&exe, sym));
		}
		jvalue* args;
		args = malloc(sizeof(jvalue)*4);
		args[0].l = obj;
		args[1].i = (jint)elf_sym_get_value(&exe, sym);
		args[2].i = (jint)elf_sym_get_size(&exe, sym);
		args[3].l = (*env)->NewString(env, (jchar*)name, (jsize)sizeof(name));

		(*env)->SetObjectArrayElement(env, functionArray, (jsize)i, (*env)->NewObject(env, function, functionConstructor, args));
	}
	(*env)->SetObjectField(env, obj, functionID, functionArray);

	//disassembly executable
	csh handle;
	cs_open(CS_ARCH_X86,CS_MODE_64,&handle);
	cs_option(handle,CS_OPT_SYNTAX,CS_OPT_SYNTAX_ATT);
	for(i = 0;i < elf_header_get_shnum(&exe);i++)
	{
		const char* name;
		if(elf_section_get_name(&exe,&exe.sections[i],&name) != -1)
		{
			if(name != ".rodata" & name != ".bss" & name !=".data")
			{
				printf(name);
				printf("\n");
				cs_insn* insn;
				size_t count;
				count = cs_disasm(handle, exe.sections[i].content, elf_section_get_size(&exe, &exe.sections[i]), elf_section_get_offset(&exe, &exe.sections[i]), 0, &insn);
				if(count)
				{
					size_t j;
					for(j = 0;j < count;j++)
					{
						printf("\t%s\t%s\n", insn[j].mnemonic, insn[j].op_str);
					}
				}
			}
		}
	}
	elf_free(&exe);
	(*env)->ReleaseStringUTFChars(env, name, filename);
}
JNIEXPORT void JNICALL Java_Executable_saveAt(JNIEnv *env, jobject obj, jstring name)
{}
JNIEXPORT jobject JNICALL Java_Executable_findSection__Ljava_lang_String_2(JNIEnv *env, jobject obj, jstring name)
{}
JNIEXPORT jobject JNICALL Java_Executable_findSection__I(JNIEnv *env, jobject obj, jint address)
{}
JNIEXPORT jobject JNICALL Java_Executable_findFunction__Ljava_lang_String_2(JNIEnv *env, jobject obj, jstring name)
{}
JNIEXPORT jobject JNICALL Java_Executable_findFunction__I(JNIEnv *env, jobject obj, jint address)
{}
