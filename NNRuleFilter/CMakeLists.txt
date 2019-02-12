cmake_minimum_required (VERSION 3.8)

project (NNRuleFilter CXX)
my_find_src_files (src_files NNRuleFilter)
add_executable (NNRuleFilter ${src_files})
my_add_compile_options (NNRuleFilter)
my_add_pch (NNRuleFilter)

my_exe_import_RisLib(NNRuleFilter)
my_exe_import_SVLib(NNRuleFilter)
my_exe_import_DisplayLib(NNRuleFilter)
my_exe_import_OpenCV(NNRuleFilter)
my_exe_import_SDL2(NNRuleFilter)
my_exe_import_DspLib(NNRuleFilter)

