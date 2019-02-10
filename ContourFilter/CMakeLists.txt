cmake_minimum_required (VERSION 3.8)

project (ContourFilter CXX)
my_find_src_files (src_files ContourFilter)
add_executable (ContourFilter ${src_files})
my_add_compile_options (ContourFilter)
my_add_pch (ContourFilter)

my_exe_import_RisLib(ContourFilter)
my_exe_import_SVLib(ContourFilter)
my_exe_import_DisplayLib(ContourFilter)
my_exe_import_OpenCV(ContourFilter)
my_exe_import_SDL2(ContourFilter)
my_exe_import_DspLib(ContourFilter)

