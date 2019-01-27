#*******************************************************************************
#*******************************************************************************
#*******************************************************************************

function(my_exe_import_CommonLib _target)

   target_link_libraries(${_target} CommonLib)
   target_include_directories(${_target} PRIVATE $<TARGET_PROPERTY:CommonLib,INTERFACE_INCLUDE_DIRECTORIES>)

endfunction()

#*******************************************************************************
#*******************************************************************************
#*******************************************************************************

function(my_exe_import_SVLib _target)

   target_link_libraries(${_target} SVLib)
   target_include_directories(${_target} PRIVATE $<TARGET_PROPERTY:SVLib,INTERFACE_INCLUDE_DIRECTORIES>)

endfunction()

#*******************************************************************************
#*******************************************************************************
#*******************************************************************************
