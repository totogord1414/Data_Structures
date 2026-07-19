# 1. 规定 CMake 的最低版本要求
cmake_minimum_required(VERSION 3.10)

# 2. 给你的项目起个霸气的名字
project(HuffmanCompression)

# 3. 规定使用 C++17 标准（现代 C++ 有很多好用的特性）
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 4. 告诉编译器：如果要找 .h 头文件，去 include 文件夹里找
include_directories(include)

# 5. 手动列出所有 .cpp 源文件（推荐做法，避免新增文件时 CMake 没发现）
set(SOURCES
    src/main.cpp
    src/CLI.cpp
    src/FileProcessor.cpp
    src/HuffmanTree.cpp
    src/HashUtils.cpp
)

# 6. 终极目标：用找到的所有 .cpp 文件，生成一个名叫 Huffman 的可执行文件
add_executable(Huffman ${SOURCES})
