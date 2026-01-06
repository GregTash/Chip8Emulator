cmake_minimum_required(VERSION 3.16.0)
project(chip8emu CXX)

set(CMAKE_CXX_FLAGS "-Wall")

# set the output directory for built objects.
# This makes sure that the dynamic library goes into the build directory automatically.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")

# This assumes the SDL source is available in vendored/SDL
add_subdirectory(vendored/SDL EXCLUDE_FROM_ALL)

# Create your game executable target as usual
add_executable(chip8emu src/main.cpp)

# Link to the actual SDL3 library.
target_link_libraries(chip8emu PRIVATE SDL3::SDL3)