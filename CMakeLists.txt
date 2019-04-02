cmake_minimum_required (VERSION 3.8)

include(MyCodeMacros.cmake)
include(MyGlobalImports.cmake)
include(MyLocalImports.cmake)
include(MyExports.cmake)

project ("Dev_Image")
my_init_global_import_variables()
my_init_export_variables()


add_subdirectory ("SVLib")
add_subdirectory ("DisplayLib")
add_subdirectory ("DisplayTest")
add_subdirectory ("Matrix")
add_subdirectory ("RCIndex")
add_subdirectory ("Numbers")
add_subdirectory ("StackFilter")
add_subdirectory ("Test")
return()

add_subdirectory ("SVLib")
add_subdirectory ("RCIndex")
return()

add_subdirectory ("DisplayLib")
add_subdirectory ("DisplayTest")
add_subdirectory ("Matrix")
add_subdirectory ("RCIndex")
add_subdirectory ("Simulate")
add_subdirectory ("SVLib")
add_subdirectory ("Test")
return()



