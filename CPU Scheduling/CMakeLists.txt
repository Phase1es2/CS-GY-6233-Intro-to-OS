cmake_minimum_required(VERSION 3.10)
project(CPU_Scheduling C)

# Add the executable from cpu.c and main.c
add_executable(cpu_scheduling
    cpu.c
    main.c
)

# Tell CMake where to find oslabs.h in the Disk Scheduling folder
target_include_directories(cpu_scheduling PRIVATE
    "${CMAKE_SOURCE_DIR}/../Disk Scheduling"
)