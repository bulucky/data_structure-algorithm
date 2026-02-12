cmake_minimum_required(VERSION 3.22)

project(DATA_STRUCTURE&&ALGORITHM)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

file(GLOB C_FILES CONFIGURE_DEPENDS 
        src/*/*.c
)

file(GLOB CXX_FILES CONFIGURE_DEPENDS 
        src/*/*.cpp
)
 
foreach(src_file IN LISTS C_FILES)
    get_filename_component(filename ${src_file} NAME_WE)
    add_executable(${filename} ${src_file})
    set_source_files_properties(${src_file} PROPERTIES LANGUAGE C)
endforeach()

foreach(src_file IN LISTS CXX_FILES)
    get_filename_component(filename ${src_file} NAME_WE)
    add_executable(${filename} ${src_file})
    set_source_files_properties(${src_file} PROPERTIES LANGUAGE CXX)
endforeach()