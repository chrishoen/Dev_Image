cmake_minimum_required (VERSION 3.8)

project (Numbers CXX)
my_find_src_files (src_files Numbers)
add_executable (Numbers ${src_files})
my_add_compile_options (Numbers)
my_add_pch (Numbers)

my_exe_import_RisLib(Numbers)
my_exe_import_SVLib(Numbers)
my_exe_import_OpenCV(Numbers)
my_exe_import_DspLib(Numbers)

