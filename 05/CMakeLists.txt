cmake_minimum_required(VERSION 3.15)
project(TreeTest LANGUAGES CXX)

# 指定 C++17 标准（支持你刚才用到的 std::optional）并开启常用编译警告
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_compile_options(-Wall -Wextra)

# 生成名为 main 的可执行文件（如果有多个 .cpp，用空格隔开写在后面即可）
add_executable(main main.cpp)