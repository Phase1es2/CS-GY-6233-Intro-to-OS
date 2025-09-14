cmake_minimum_required(VERSION 3.10)
project(OSLabs C)

set(CMAKE_C_STANDARD 99)

# Add an executable that links all required source files
cmake_minimum_required(VERSION 3.10)
project(oslabs C)

add_executable(oslabs
    main.c
    disk.c
    test.c
)
# If you want a separate test binary (without main.c)

#add_executable(tests test.c disk.c )