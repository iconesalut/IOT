cmake_minimum_required(VERSION 2.8)

project(IOT)
find_package(JNI REQUIRED)
find_package(Java REQUIRED)
include(UseJava)
include_directories(${JNI_INCLUDE_DIRS})
set(SOURCE
    src/Elfparse/elf_free.c
    src/Elfparse/elf_get_strtab.c
    src/Elfparse/elf_get_symtab.c
    src/Elfparse/elf_header_get_ph.c
    src/Elfparse/elf_header_get_sh.c
    src/Elfparse/elf_header_get.c
    src/Elfparse/elf_load_buffer.c
    src/Elfparse/elf_load_file.c
    src/Elfparse/elf_load_header.c
    src/Elfparse/elf_load_sections.c
    src/Elfparse/elf_section_get.c
    src/Elfparse/elf_section_get2.c
    src/Elfparse/elf_strtab.c
    src/Elfparse/elf_sym.c
    src/Elfparse/elf_sym2.c
    src/Elfparse/elf_symtab.c
    src/Elfparse/utils.c
    src/Executable.c
)
set(SOURCE_JAVA
    java/Function.java
    java/Section.java
    java/Executable.java
    java/IOT.java
)
add_library(${PROJECT_NAME} SHARED ${SOURCE})
add_jar(${PROJECT_NAME}j
    SOURCE SOURCE_JAVA
    ENTRY_POINT IOT
)
target_link_libraries(
    ${PROJECT_NAME}
    capstone
)
