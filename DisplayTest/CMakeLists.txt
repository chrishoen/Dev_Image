cmake_minimum_required (VERSION 3.8)

project (DisplayTest CXX)
my_find_src_files (src_files DisplayTest)
add_executable (DisplayTest ${src_files})
my_add_compile_options (DisplayTest)
my_add_pch (DisplayTest)

my_inc_import_RisLib(DisplayTest)
my_inc_import_OpenCV(DisplayTest)
my_inc_import_SDL2(DisplayTest)
my_inc_import_DisplayLib(DisplayTest)
my_inc_import_SVLib(DisplayTest)

my_lib_import_OpenCV(DisplayTest)
my_lib_import_SDL2(DisplayTest)
my_lib_import_DisplayLib(DisplayTest)
my_lib_import_SVLib(DisplayTest)
my_lib_import_RisLib(DisplayTest)

