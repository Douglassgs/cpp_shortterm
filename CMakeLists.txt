cmake_minimum_required(VERSION 3.10)

# 设置项目名称和语言
project(cpp_shortterm CXX)

# 设置 C++ 标准为 C++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 由于 main.cpp 文件通过 #include 指令包含了其他 .cpp 文件，
# 为了避免链接时出现多重定义错误，add_executable 命令只应包含 main.cpp。
add_executable(cpp_shortterm main.cpp
)

# 为目标 cpp_shortterm 添加头文件搜索路径。
# 这使得编译器能够找到 "inc" 目录下的头文件，例如 DoubleLinkedList.hpp。
# 建议您将 src/library.cpp 中的 #include "../inc/DoubleLinkedList.hpp"
# 修改为 #include "DoubleLinkedList.hpp" 以配合此设置。
target_include_directories(cpp_shortterm PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/inc)