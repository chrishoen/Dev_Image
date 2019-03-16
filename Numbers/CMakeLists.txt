cmake_minimum_required (VERSION 3.8)

project (Numbers CXX)
my_find_src_files (src_files Numbers)
add_executable (Numbers ${src_files})
my_add_compile_options (Numbers)
my_add_pch (Numbers)

my_inc_import_RisLib(Numbers)
my_inc_import_SVLib(Numbers)
my_inc_import_CPrintLib(Numbers)
my_inc_import_OpenCV(Numbers)

my_lib_import_OpenCV(Numbers)
my_lib_import_SVLib(Numbers)
my_lib_import_CPrintLib(Numbers)
my_lib_import_RisLib(Numbers)

