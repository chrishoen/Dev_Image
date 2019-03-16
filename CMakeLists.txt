cmake_minimum_required (VERSION 3.8)

include(MyCMake.cmake)
include(MyImports.cmake)
include(MyLocalImports.cmake)

project ("Dev_Image")
my_init_variables()
my_init_import_variables()


add_subdirectory ("CPrintLib")
add_subdirectory ("SVLib")
add_subdirectory ("DisplayLib")
add_subdirectory ("DisplayTest")
add_subdirectory ("Session")
add_subdirectory ("StackFilter")
return()

add_subdirectory ("CPrintLib")
add_subdirectory ("Session")
return()

add_subdirectory ("DisplayTest")
add_subdirectory ("CPrintLib")
add_subdirectory ("DisplayLib")
add_subdirectory ("SVLib")
return()

add_subdirectory ("SVLib")
add_subdirectory ("RCIndex")
return()

add_subdirectory ("CPrintLib")
add_subdirectory ("DisplayLib")
add_subdirectory ("DisplayTest")
add_subdirectory ("Matrix")
add_subdirectory ("RCIndex")
add_subdirectory ("Simulate")
add_subdirectory ("SVLib")
add_subdirectory ("Test")
return()


add_subdirectory ("SVLib")

