cmake_minimum_required(VERSION 2.8)

project(IOT)
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
    src/operand.c
    src/function.c
    src/instruction.c
    src/executable.c
    src/main.c
)
add_executable(${PROJECT_NAME} ${SOURCE})
target_link_libraries(
    ${PROJECT_NAME}
    capstone
)
