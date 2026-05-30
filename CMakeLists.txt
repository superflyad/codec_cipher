cmake_minimum_required(VERSION 3.16)

project(codec_cipher VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(codec_cipher
    app/main.cpp
    src/DimensionalObject.cpp
    src/Laboratory.cpp
    src/Persistence.cpp
    src/TerminalView.cpp
)

target_include_directories(codec_cipher PRIVATE include)
