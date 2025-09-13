cmake_minimum_required(VERSION 3.22)

project(DATA_STRUCTURE&&ALGORITHM)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

# 递归遍历src目录找到所有源文件.cpp .c存入列表SRC_FILES
file(GLOB SRC_FILES CONFIGURE_DEPENDS
        src/*/*.cpp 
        src/*/*.c
)
 
# 遍历列表SRC_FILES所有源文件
foreach(src_file IN LISTS SRC_FILES)
    # 从路径中提取文件名（去掉目录和扩展名）
    get_filename_component(filename ${src_file} NAME_WE)
    # 生成的对应的可执行文件
    add_executable(${filename} ${src_file})
endforeach()