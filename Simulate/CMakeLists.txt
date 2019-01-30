cmake_minimum_required (VERSION 3.8)

project (Simulate CXX)
my_find_src_files (src_files Simulate)
add_executable (Simulate ${src_files})
my_add_compile_options (Simulate)
my_add_pch (Simulate)

my_exe_import_RisLib(Simulate)
my_exe_import_SVLib(Simulate)
my_exe_import_DisplayLib(Simulate)
my_exe_import_OpenCV(Simulate)
my_exe_import_SDL2(Simulate)
my_exe_import_DspLib(Simulate)

