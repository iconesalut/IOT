cmake_minimum_required(VERSION 2.8)

project(IOT)
include(UseJava)
add_compile_options("-std=c++11")
set(SOURCE
    src/operand.cpp
    src/instruction.cpp
    src/function.cpp
    src/executable.cpp
)
add_executable(${PROJECT_NAME} ${SOURCE})
target_link_libraries(
    ${PROJECT_NAME}
    LIEF
    capstone
)
