#*******************************************************************************
#*******************************************************************************
#*******************************************************************************

function(my_init_import_variables)

   if(MSVC)
      set (MyRisLibIncludePath "C:\\MyTools\\MyLib\\include\\RisLib" PARENT_SCOPE)
      set (MyRisLibImportPath  "C:\\MyTools\\MyLib\\lib\\RisLib.lib" PARENT_SCOPE)
      set (MyDspLibIncludePath "C:\\MyTools\\MyLib\\include\\DspLib" PARENT_SCOPE)
      set (MyDspLibImportPath  "C:\\MyTools\\MyLib\\lib\\DspLib.lib" PARENT_SCOPE)
      set (MyOpenCVIncludePath "C:\\MyTools\\opencv\\build\\include" PARENT_SCOPE)
      set (MyOpenCVImportPath  "C:\\MyTools\\opencv\\build\\x64\\vc15\\lib\\opencv_world343.lib" PARENT_SCOPE)
      set (MyEigenIncludePath  "C:\\MyTools\\Eigen" PARENT_SCOPE)
   else()
      set (MyRisLibIncludePath "/usr/local/include/RisLib" PARENT_SCOPE)
      set (MyRisLibImportPath  "/usr/local/lib/libRisLib.a" PARENT_SCOPE)
      set (MyDspLibIncludePath "/usr/local/include/DspLib" PARENT_SCOPE)
      set (MyDspLibImportPath  "/usr/local/lib/libDspLib.a" PARENT_SCOPE)
      set (MyOpenCVIncludePath "C:\\MyTools\\opencv\\build\\include" PARENT_SCOPE)
      set (MyOpenCVImportPath  "C:\\MyTools\\opencv\\build\\x64\\vc15\\lib\\opencv_world343.lib" PARENT_SCOPE)
      set (MyEigenIncludePath "/usr/include/eigen3" PARENT_SCOPE)
   endif()
endfunction()

#*******************************************************************************
#*******************************************************************************
#*******************************************************************************

function(my_exe_import_RisLib _target)

   add_library(RisLib STATIC IMPORTED)
   set_target_properties(RisLib PROPERTIES IMPORTED_LOCATION ${MyRisLibImportPath})

   if (MSVC)
      target_link_libraries(RisLib INTERFACE ws2_32)
      target_link_libraries(RisLib INTERFACE winmm)
   else()
      set(THREADS_PREFER_PTHREAD_FLAG ON)
      find_package(Threads REQUIRED)
      target_link_libraries(RisLib INTERFACE Threads::Threads)
   endif()

   target_include_directories(${_target} PRIVATE ${MyRisLibIncludePath})
   target_link_libraries(${_target} RisLib)

endfunction()

#*******************************************************************************
#*******************************************************************************
#*******************************************************************************

function(my_lib_import_RisLib _target)

   target_include_directories(${_target} PUBLIC ${MyRisLibIncludePath})

endfunction()

#*******************************************************************************
#*******************************************************************************
#*******************************************************************************

function(my_exe_import_DspLib _target)

   add_library(DspLib STATIC IMPORTED)
   set_target_properties(DspLib PROPERTIES IMPORTED_LOCATION ${MyDspLibImportPath})

   target_include_directories(${_target} PRIVATE ${MyDspLibIncludePath})
   target_link_libraries(${_target} DspLib)

endfunction()

#*******************************************************************************
#*******************************************************************************
#*******************************************************************************

function(my_lib_import_DspLib _target)

   target_include_directories(${_target} PUBLIC ${MyDspLibIncludePath})

endfunction()

#*******************************************************************************
#*******************************************************************************
#*******************************************************************************

function(my_exe_import_OpenCV _target)

   add_library(OpenCV STATIC IMPORTED)
   set_target_properties(OpenCV PROPERTIES IMPORTED_LOCATION ${MyOpenCVImportPath})

   target_include_directories(${_target} PRIVATE ${MyOpenCVIncludePath})
   target_link_libraries(${_target} OpenCV)

endfunction()

#*******************************************************************************
#*******************************************************************************
#*******************************************************************************

function(my_lib_import_OpenCV _target)

   target_include_directories(${_target} PUBLIC ${MyOpenCVIncludePath})

endfunction()

