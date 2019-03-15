cmake_minimum_required (VERSION 3.8)

project (DisplayLib CXX)

my_find_src_files (src_files DisplayLib)
my_find_inc_files (inc_files)
add_library (DisplayLib STATIC ${src_files})
my_add_compile_options (DisplayLib)
my_add_pch (DisplayLib)

target_include_directories(DisplayLib INTERFACE ${PROJECT_SOURCE_DIR})

my_inc_import_RisLib(DisplayLib)
my_inc_import_SDL2(DisplayLib)
my_inc_import_OpenCV(DisplayLib)
