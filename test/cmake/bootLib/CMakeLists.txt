
cmake_minimum_required(VERSION 3.22)

project(bootLib)
#compile as lib, not exe
add_library(bootLib INTERFACE)

# Enable CMake support for ASM and C languages
enable_language(C ASM CXX)


target_include_directories(bootLib INTERFACE
    ../../bootLib/core/include
    ../../bootLib/SEGGER/include
    ../../bootLib/CMSIS/include
)
FILE(GLOB_RECURSE SOURCES
    "../../bootLib/*.cpp"
    "../../bootLib/*.s"
    "../../bootLib/*.S"
)
target_sources(bootLib INTERFACE
    ${SOURCES}
)

# Validate that bootLib code is compatible with C standard
if(CMAKE_CXX_STANDARD LESS 20)
    message(ERROR "Generated code requires C++20 or higher")
endif()


