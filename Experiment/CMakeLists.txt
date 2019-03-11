cmake_minimum_required (VERSION 3.8)

project (Experiment CXX)
my_find_src_files (src_files Experiment)
add_executable (Experiment ${src_files})
my_add_compile_options (Experiment)
my_add_pch (Experiment)

my_exe_import_RisLib(Experiment)
return()


find_package(RisLib CONFIG REQUIRED PATHS ${MyRisLibConfigPath} NO_DEFAULT_PATH)
target_include_directories(Experiment PRIVATE RisLib)
target_link_libraries(Experiment RisLib)

