cmake_minimum_required (VERSION 3.8)

project (DisplayTest CXX)
my_find_src_files (src_files DisplayTest)
add_executable (DisplayTest ${src_files})
my_add_compile_options (DisplayTest)
my_add_pch (DisplayTest)

my_exe_import_RisLib(DisplayTest)
my_exe_import_OpenCV(DisplayTest)
my_exe_import_SDL2(DisplayTest)
my_exe_import_DisplayLib(DisplayTest)
my_exe_import_DspLib(DisplayTest)

