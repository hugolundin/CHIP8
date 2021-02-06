cmake_minimum_required(VERSION 3.1...3.16)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

project(chip8 VERSION 0.1.0 LANGUAGES C)

include_directories(src)
add_subdirectory(src)
