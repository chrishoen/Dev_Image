cmake_minimum_required (VERSION 3.8)

include(MyCMake.cmake)
include(MyImports.cmake)
include(MyLocalImports.cmake)

project ("Dev_Image")
my_init_variables()
my_init_import_variables()

add_subdirectory ("SVLib")
return()

add_subdirectory ("CommonLib")
add_subdirectory ("ImageGen")
add_subdirectory ("SVLib")
add_subdirectory ("Test")
