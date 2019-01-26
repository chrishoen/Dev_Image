cmake_minimum_required (VERSION 3.8)

project (GenImage CXX)
my_find_src_files (src_files GenImage)
add_executable (GenImage ${src_files})
my_add_compile_options (GenImage)
my_add_pch (GenImage)

target_include_directories(GenImage PUBLIC ${PROJECT_SOURCE_DIR})

my_exe_import_RisLib(GenImage)
my_exe_import_DspLib(GenImage)
my_exe_import_OpenCV(GenImage)

target_include_directories(GenImage PUBLIC CommonLib)
target_link_libraries(GenImage CommonLib)

return()

find_package(OpenCV CONFIG REQUIRED PATHS ${MyOpenCVConfigPath} NO_DEFAULT_PATH)
target_include_directories(GenImage PUBLIC OpenCV)
target_link_libraries(GenImage OpenCV)





