cmake_minimum_required(VERSION 2.8)

set(CMAKE_MODULE_PATH /home/icone/github/IOT/)

project(IOT)
set(SOURCE
    core/Elfparse/elf_free.c
    core/Elfparse/elf_get_strtab.c
    core/Elfparse/elf_get_symtab.c
    core/Elfparse/elf_header_get_ph.c
    core/Elfparse/elf_header_get_sh.c
    core/Elfparse/elf_header_get.c
    core/Elfparse/elf_load_buffer.c
    core/Elfparse/elf_load_file.c
    core/Elfparse/elf_load_header.c
    core/Elfparse/elf_load_sections.c
    core/Elfparse/elf_section_get.c
    core/Elfparse/elf_section_get2.c
    core/Elfparse/elf_strtab.c
    core/Elfparse/elf_sym.c
    core/Elfparse/elf_sym2.c
    core/Elfparse/elf_symtab.c
    core/Elfparse/utils.c
    core/operand.c
    core/function.c
    core/instruction.c
    core/executable.c
)
add_library(${PROJECT_NAME} SHARED ${SOURCE})
target_link_libraries(
    ${PROJECT_NAME}
    capstone
)

install(TARGETS ${PROJECT_NAME}
    DESTINATION /usr/lib/
)
install(DIRECTORY ${PROJECT_SOURCE_DIR}/sample/
    DESTINATION /usr/share/IOT/
)