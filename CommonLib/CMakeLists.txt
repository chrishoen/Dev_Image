cmake_minimum_required (VERSION 3.8)

project (CommonLib CXX)

my_find_src_files (src_files CommonLib)
my_find_inc_files (inc_files)
add_library (CommonLib STATIC ${src_files})
my_add_compile_options (CommonLib)
my_add_pch (CommonLib)

target_include_directories(CommonLib INTERFACE ${PROJECT_SOURCE_DIR})

my_inc_import_RisLib(CommonLib)
my_inc_import_DspLib(CommonLib)

