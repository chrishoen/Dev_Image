cmake_minimum_required (VERSION 3.8)

project (Matrix CXX)
my_find_src_files (src_files Matrix)
add_executable (Matrix ${src_files})
my_add_compile_options (Matrix)
my_add_pch (Matrix)

my_exe_import_RisLib(Matrix)
my_exe_import_SVLib(Matrix)
my_exe_import_OpenCV(Matrix)
my_exe_import_CommonLib(Matrix)
my_exe_import_DspLib(Matrix)

