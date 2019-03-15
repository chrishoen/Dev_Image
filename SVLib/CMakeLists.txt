cmake_minimum_required (VERSION 3.8)

project (SVLib CXX)

my_find_src_files (src_files SVLib)
my_find_inc_files (inc_files)
add_library (SVLib STATIC ${src_files})
my_add_compile_options (SVLib)
my_add_pch (SVLib)

target_include_directories(SVLib INTERFACE ${PROJECT_SOURCE_DIR})

my_inc_import_OpenCV(SVLib)
my_inc_import_RisLib(SVLib)
my_inc_import_DspLib(SVLib)
