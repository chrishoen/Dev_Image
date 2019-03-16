cmake_minimum_required (VERSION 3.8)

project (Session CXX)
my_find_src_files (src_files Session)
add_executable (Session ${src_files})
my_add_compile_options (Session)
my_add_pch (Session)

my_inc_import_RisLib(Session)
my_inc_import_CPrintLib(Session)

my_lib_import_CPrintLib(Session)
my_lib_import_RisLib(Session)

install(TARGETS Session DESTINATION ${MyInstallPath})


