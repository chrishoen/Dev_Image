cmake_minimum_required (VERSION 3.8)

include(MyCMake.cmake)
include(MyImports.cmake)
include(MyLocalImports.cmake)

project ("Dev_Image")
my_init_variables()
my_init_import_variables()

add_subdirectory ("CommonLib")
add_subdirectory ("GenImage")
add_subdirectory ("Test")
