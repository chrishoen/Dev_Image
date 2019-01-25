cmake_minimum_required (VERSION 3.8)

project (CommonLib CXX)

my_find_src_files (src_files CommonLib)
my_find_inc_files (inc_files)
add_library (CommonLib STATIC ${src_files})
my_add_compile_options (CommonLib)
my_add_pch (CommonLib)

target_include_directories(CommonLib PUBLIC ${PROJECT_SOURCE_DIR})

find_package(DspLib CONFIG REQUIRED PATHS ${MyDspLibConfigPath} NO_DEFAULT_PATH)
target_include_directories(CommonLib PUBLIC DspLib)
target_link_libraries(CommonLib DspLib)
