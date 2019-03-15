cmake_minimum_required (VERSION 3.8)

project (RCIndex CXX)
my_find_src_files (src_files RCIndex)
add_executable (RCIndex ${src_files})
my_add_compile_options (RCIndex)
my_add_pch (RCIndex)

my_inc_import_RisLib(RCIndex)
my_inc_import_SVLib(RCIndex)
my_inc_import_OpenCV(RCIndex)
my_inc_import_DspLib(RCIndex)

my_lib_import_OpenCV(RCIndex)
my_lib_import_SVLib(RCIndex)
my_lib_import_RisLib(RCIndex)
my_lib_import_DspLib(RCIndex)

