cmake_minimum_required (VERSION 3.8)

project (RCIndex CXX)
my_find_src_files (src_files RCIndex)
add_executable (RCIndex ${src_files})
my_add_compile_options (RCIndex)
my_add_pch (RCIndex)

my_exe_import_RisLib(RCIndex)
my_exe_import_SVLib(RCIndex)
my_exe_import_OpenCV(RCIndex)
my_exe_import_DspLib(RCIndex)

