cmake_minimum_required (VERSION 3.8)

project (Matrix CXX)
my_find_src_files (src_files Matrix)
add_executable (Matrix ${src_files})
my_add_compile_options (Matrix)
my_add_pch (Matrix)

my_inc_import_RisLib(Matrix)
my_inc_import_SVLib(Matrix)
my_inc_import_OpenCV(Matrix)
my_inc_import_CommonLib(Matrix)
my_inc_import_DspLib(Matrix)

my_lib_import_OpenCV(Matrix)
my_lib_import_SVLib(Matrix)
my_lib_import_CommonLib(Matrix)
my_lib_import_RisLib(Matrix)
my_lib_import_DspLib(Matrix)

