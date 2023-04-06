# CMake 最低版本号要求
cmake_minimum_required (VERSION 3.0)

# 项目信息
project (MyProject)

# 设置 C++ 标准
set (CMAKE_CXX_STANDARD 17)

# 指定头文件目录
include_directories (
    ${PROJECT_SOURCE_DIR}/include
)

# 添加一个子目录，指定包含的CMakeLists.txt所在的路径
add_subdirectory (src)

# 指定生成目标
#add_executable (MyProject main.cpp)

# 指定库文件目录
link_directories (
    ${PROJECT_SOURCE_DIR}/lib
)
