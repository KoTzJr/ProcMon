cmake_minimum_required(VERSION 4.1)
project(ProcMon)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(.)

add_executable(ProcMon
        main.cpp
        PCMOV.cpp
        PCMOV.h)

target_link_libraries(ProcMon PRIVATE psapi)