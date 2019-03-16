cmake_minimum_required (VERSION 3.8)

project (CPrintLib CXX)

my_find_src_files (src_files CPrintLib)
my_find_inc_files (inc_files)
add_library (CPrintLib STATIC ${src_files})
my_add_compile_options (CPrintLib)
my_add_pch (CPrintLib)

target_include_directories(CPrintLib INTERFACE ${PROJECT_SOURCE_DIR})

my_inc_import_RisLib(CPrintLib)
my_inc_import_DspLib(CPrintLib)

