cmake_minimum_required(VERSION 2.8)

project(IOT)
find_package(JNI REQUIRED)
find_package(Java REQUIRED)
include(UseJava)
include_directories(${JNI_INCLUDE_DIRS})
set(SOURCE
    src/Executable.c
)
add_library(${PROJECT_NAME} SHARED ${SOURCE})
add_jar(${PROJECT_NAME}j
    SOURCE java/Executable.java java/IOT.java
    ENTRY_POINT IOT
)
target_link_libraries(
    ${PROJECT_NAME}
    LIEF
    capstone
)
