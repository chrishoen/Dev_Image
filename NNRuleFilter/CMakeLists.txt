cmake_minimum_required (VERSION 3.8)

project (NNRuleFilter CXX)
my_find_src_files (src_files NNRuleFilter)
add_executable (NNRuleFilter ${src_files})
my_add_compile_options (NNRuleFilter)
my_add_pch (NNRuleFilter)

my_inc_import_RisLib(NNRuleFilter)
my_inc_import_SVLib(NNRuleFilter)
my_inc_import_DisplayLib(NNRuleFilter)
my_inc_import_OpenCV(NNRuleFilter)
my_inc_import_SDL2(NNRuleFilter)

my_lib_import_OpenCV(NNRuleFilter)
my_lib_import_SDL2(NNRuleFilter)
my_lib_import_SVLib(NNRuleFilter)
my_lib_import_DisplayLib(NNRuleFilter)
my_lib_import_RisLib(NNRuleFilter)

