cmake_minimum_required (VERSION 3.8)

project (GenImage CXX)
my_find_src_files (src_files GenImage)
add_executable (GenImage ${src_files})
my_add_compile_options (GenImage)
my_add_pch (GenImage)

target_include_directories(GenImage PRIVATE CommomLib)
target_link_libraries(GenImage CommonLib)

