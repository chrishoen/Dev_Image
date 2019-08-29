cmake_minimum_required (VERSION 3.8)

set (CMAKE_USER_MAKE_RULES_OVERRIDE "${CMAKE_CURRENT_LIST_DIR}/MyOverrides.cmake")
include(MyPrecompiledHeader.cmake)
include(MyCodeMacros.cmake)
include(MyGlobalImports.cmake)
include(MyLocalImports.cmake)

project ("Dev_Image")
my_init_global_import_variables()


add_subdirectory ("SVLib")
add_subdirectory ("DisplayLib")
add_subdirectory ("StackFilter")
return()

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



