cmake_minimum_required(VERSION 3.10)

# 1. 项目名称
project(CainiaoDeliverySystem VERSION 1.0)

# 2. 指定 C++ 标准（项目要求 c++17）
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 3. 指定头文件的包含目录
# 这样在 src 里的代码直接写 #include "models/package.h" 就能找到 include 文件夹下的内容
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# 4. 自动查找 src 目录下的所有 .cpp 源文件
# GLOB_RECURSE 会递归查找，也就是 src 里面子文件夹的 .cpp 也会被找到
file(GLOB_RECURSE SOURCES "src/*.cpp")

# 5. 生成可执行文件
# 把找到的所有 SOURCES 编译成一个名字叫 CainiaoDeliverySystem 的可执行程序
add_executable(${PROJECT_NAME} ${SOURCES})
