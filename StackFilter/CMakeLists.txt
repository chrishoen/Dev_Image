﻿cmake_minimum_required (VERSION 3.8)

project (StackFilter CXX)
my_find_src_files (src_files StackFilter)
add_executable (StackFilter ${src_files})
my_add_compile_options (StackFilter)
my_add_pch (StackFilter)

my_inc_import_RisLib(StackFilter)
my_inc_import_SVLib(StackFilter)
my_inc_import_DisplayLib(StackFilter)
my_inc_import_OpenCV(StackFilter)
my_inc_import_SDL2(StackFilter)
my_inc_import_CPrintLib(StackFilter)

my_lib_import_OpenCV(StackFilter)
my_lib_import_SDL2(StackFilter)
my_lib_import_SVLib(StackFilter)
my_lib_import_DisplayLib(StackFilter)
my_lib_import_CPrintLib(StackFilter)
my_lib_import_RisLib(StackFilter)

install(TARGETS StackFilter DESTINATION ${MyInstallPath})
