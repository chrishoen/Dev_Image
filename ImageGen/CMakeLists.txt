cmake_minimum_required (VERSION 3.8)

project (ImageGen CXX)
my_find_src_files (src_files ImageGen)
add_executable (ImageGen ${src_files})
my_add_compile_options (ImageGen)
my_add_pch (ImageGen)

my_exe_import_RisLib(ImageGen)
my_exe_import_SVLib(ImageGen)
my_exe_import_OpenCV(ImageGen)
my_exe_import_DspLib(ImageGen)

