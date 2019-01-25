cmake_minimum_required (VERSION 3.8)

include(MyCMake.cmake)

project ("Dev_Image")
my_init_variables()

add_subdirectory ("CommonLib")
add_subdirectory ("Test")
