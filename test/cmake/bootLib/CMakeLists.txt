
cmake_minimum_required(VERSION 3.22)

project(bootLib)
#compile as lib, not exe
add_library(bootLib INTERFACE)

# Enable CMake support for ASM and C languages
enable_language(C ASM CXX)


target_include_directories(bootLib INTERFACE
    ../../bootLib/include
    ../../bootLib/include/CMSIS
    ../../bootLib/include/SEGGER
)

FILE(GLOB SOURCES "../../bootLib/*.cpp")
FILE(GLOB SEGGER_SOURCES_CXX "../../bootLib/SEGGER/*.cpp")
FILE(GLOB SEGGER_SOURCES_ASM "../../bootLib/SEGGER/*.S")
FILE(GLOB ASM_SOURCES "../../bootLib/*.s")
target_sources(bootLib INTERFACE
    ${SOURCES}
    ${ASM_SOURCES}
    ${SEGGER_SOURCES_CXX}
    ${SEGGER_SOURCES_ASM}
)

# Validate that bootLib code is compatible with C standard
if(CMAKE_CXX_STANDARD LESS 20)
    message(ERROR "Generated code requires C++20 or higher")
endif()


