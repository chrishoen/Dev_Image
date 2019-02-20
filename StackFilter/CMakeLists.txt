cmake_minimum_required (VERSION 3.8)

project (StackFilter CXX)
my_find_src_files (src_files StackFilter)
add_executable (StackFilter ${src_files})
my_add_compile_options (StackFilter)
my_add_pch (StackFilter)

my_exe_import_RisLib(StackFilter)
my_exe_import_SVLib(StackFilter)
my_exe_import_DisplayLib(StackFilter)
my_exe_import_OpenCV(StackFilter)
my_exe_import_SDL2(StackFilter)
my_exe_import_CommonLib(StackFilter)
my_exe_import_DspLib(StackFilter)

