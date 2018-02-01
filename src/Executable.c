#include "Executable.h"
#include <stdio.h>
#include <stdlib.h>
#include <LIEF/LIEF.h>

JNIEXPORT void JNICALL Java_Executable_initBinary(JNIEnv *env, jobject obj, jstring name)
{
    const char* filename = (*env)->GetStringUTFChars(env, name, 0);
    Elf_Binary_t* binary = elf_parse(filename);
    fprintf(stdout, "Dynamic symbols:\n");
    Elf_Symbol_t** dynamic_symbols = binary->dynamic_symbols;
    int i;
    for (i = 0; dynamic_symbols[i] != NULL; ++i) {
      Elf_Symbol_t* symbol = dynamic_symbols[i];
      char import_export = "";
  
      if (symbol->is_imported) {
        import_export = 'I';
      }
  
      if (symbol->is_imported) {
        import_export = 'E';
      }
  
      fprintf(stdout, ""
          "%-20s "
          "%-10s "
          "%-10s "
          "0x%02x "
          "0x%02x"
          "0x%010" PRIx64 " "
          "0x%06" PRIx64 " "
          "%-3s "
          "\n",
          symbol->name,
          ELF_SYMBOL_TYPES_to_string(symbol->type),
          SYMBOL_BINDINGS_to_string(symbol->binding),
          symbol->other,
          symbol->shndx,
          symbol->value,
          symbol->size,
          import_export
          );
    }
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
