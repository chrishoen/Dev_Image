#*******************************************************************************
#*******************************************************************************
#*******************************************************************************

function(my_lib_import_SVLib _target)

   target_link_libraries(${_target} SVLib)

endfunction()

function(my_inc_import_SVLib _target)

   target_include_directories(${_target} PRIVATE $<TARGET_PROPERTY:SVLib,INTERFACE_INCLUDE_DIRECTORIES>)

endfunction()

#*******************************************************************************
#*******************************************************************************
#*******************************************************************************

function(my_lib_import_DisplayLib _target)

   target_link_libraries(${_target} DisplayLib)

endfunction()

function(my_inc_import_DisplayLib _target)

   target_include_directories(${_target} PRIVATE $<TARGET_PROPERTY:DisplayLib,INTERFACE_INCLUDE_DIRECTORIES>)

endfunction()

#*******************************************************************************
#*******************************************************************************
#*******************************************************************************

