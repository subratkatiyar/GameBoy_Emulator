cmake_minimum_required(VERSION 3.10)
project(GameboyEmulator)

# Set C standard to C11
set(CMAKE_C_STANDARD 11)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

file(GLOB SOURCES "src/*.cpp")

# Include directories
include_directories(include)

# Create executable
add_executable(gameboy_emulator ${SOURCES})

# Include SFML headers
target_include_directories(gameboy_emulator PRIVATE ${SFML_INCLUDE_DIRS})

# Link SFML libraries
target_link_libraries(gameboy_emulator PRIVATE sfml-graphics)

target_compile_features(gameboy_emulator PRIVATE cxx_std_17)

if(WIN32)
    add_custom_command(
        TARGET gameboy_emulator
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:gameboy_emulator>
        VERBATIM)
endif()

install(TARGETS gameboy_emulator)