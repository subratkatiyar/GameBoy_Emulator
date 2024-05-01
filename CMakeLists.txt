cmake_minimum_required(VERSION 3.10)
project(GameboyEmulator C)

# Set C standard to C11
set(CMAKE_C_STANDARD 11)

# Set source files
set(SOURCES 
    src/main.c
    src/memory.c
    src/cpu.c
    src/INS_load.c
    # Add other source files here as needed
)

# Include directories
include_directories(include)

# Create executable
add_executable(gameboy_emulator ${SOURCES})

# Optional: Specify additional compiler flags
# target_compile_options(gameboy_emulator PRIVATE -Wall -Wextra)

# Optional: Install target (if needed)
# install(TARGETS gameboy_emulator DESTINATION bin)
