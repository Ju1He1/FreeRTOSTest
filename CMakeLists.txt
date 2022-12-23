cmake_minimum_required(VERSION 3.22.0)
project("FreeRTOS")
enable_language( C CXX ASM )
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

cmake_policy(SET CMP0091 NEW)
#### sources

set(MODULE_SOURCES 
  "Source/croutine.c"
  "Source/event_groups.c"
  "Source/list.c"
  "Source/queue.c"
  "Source/stream_buffer.c"
  "Source/tasks.c"
  "Source/timers.c"
  "Source/include/atomic.h"
  "Source/include/croutine.h"
  "Source/include/deprecated_definitions.h"
  "Source/include/event_groups.h"
  "Source/include/FreeRTOS.h"
  "Source/include/list.h"
  "Source/include/message_buffer.h"
  "Source/include/mpu_prototypes.h"
  "Source/include/mpu_wrappers.h"
  "Source/include/portable.h"
  "Source/include/projdefs.h"
  "Source/include/queue.h"
  "Source/include/semphr.h"
  "Source/include/stack_macros.h"
  "Source/include/StackMacros.h"
  "Source/include/stream_buffer.h"
  "Source/include/task.h"
  "Source/include/timers.h"
  "CMSIS_RTOS/cmsis_os.h"
  "CMSIS_RTOS/cmsis_os.c"
  "user/FreeRTOSHooks.h" "user/FreeRTOSHooks.c"
  "user/trcSnapshotConfig.h"
  "user/trcConfig.h"
  "user/commonFunctions.h" "user/commonFunctions.c"
  "Source/portable/MemMang/heap_4.c"
  "CMSIS/Include/cmsis_armcc.h" 
  "CMSIS/Include/cmsis_armclang.h"
  "CMSIS/Include/cmsis_compiler.h" 
  "CMSIS/Include/cmsis_gcc.h" 
  "CMSIS/Include/cmsis_iccarm.h" 
  "CMSIS/Include/cmsis_version.h"
  "CMSIS/Include/core_armv8mbl.h" 
  "CMSIS/Include/core_armv8mml.h" 
  "CMSIS/Include/core_cm0.h" 
  "CMSIS/Include/core_cm0plus.h"
  "CMSIS/Include/core_cm1.h"
  "CMSIS/Include/core_cm23.h" 
  "CMSIS/Include/core_cm3.h" 
  "CMSIS/Include/core_cm33.h" 
  "CMSIS/Include/core_cm4.h" 
  "CMSIS/Include/core_cm7.h"
  "CMSIS/Include/core_sc000.h" 
  "CMSIS/Include/core_sc300.h" 
  "CMSIS/Include/mpu_armv7.h" 
  "CMSIS/Include/mpu_armv8.h" 
  "CMSIS/Include/tz_context.h")



if(BUILD_TARGET)
  
  list(APPEND MODULE_SOURCES
    #this is the ARM port TODO replace this in windows simmulation
    "cpp11_gcc/condition_variable.cpp"
    "cpp11_gcc/condition_variable.h"
    "cpp11_gcc/critical_section.h"
    "cpp11_gcc/freertos_time.cpp"
    "cpp11_gcc/freertos_time.h"
    "cpp11_gcc/gthr_key.cpp"
    "cpp11_gcc/gthr_key.h"
    "cpp11_gcc/gthr_key_type.h"
    "cpp11_gcc/thread.cpp"
    "cpp11_gcc/thread_gthread.h"
    "cpp11_gcc/bits/gthr-default.h"
  )
else()
  #ADD Debug Logger (only in Simmulation)
  list(APPEND MODULE_SOURCES
    "user/AssertWithTrace.h" "user/AssertWithTrace.c"
    "user/FreeRTOSHooks.h"
    "user/FreeRTOSHooks.c"
    "user/CMSIS_Simulation_Mock.h" "user/CMSIS_Simulation_Mock.c"
  )
  if(WIN32)  
    list(APPEND MODULE_SOURCES 
      "user/Run-time-stats-utils_windows.c"
    )
  elseif(UNIX)
    #added by macro
  else()
    message(FATAL_ERROR "Please provide a proper port for your compiler")
  endif()
endif()

# add the port sources
if(BUILD_TARGET)
  list(APPEND MODULE_SOURCES 
    "Source/portable/GCC/ARM_CM4F/port.c" "Source/portable/GCC/ARM_CM4F/portmacro.h"
  )
else()

  if(WIN32)
    list(APPEND MODULE_SOURCES 
     "Source/portable/MSVC-MingW/portmacro.h" 
     "user/Run-time-stats-utils_windows.c" 
     "Source/portable/MSVC-MingW/port_exitable.c"
    )
  elseif(UNIX)
  list(APPEND MODULE_SOURCES 
    "Source/portable/ThirdParty/GCC/Posix/portmacro.h"
    "Source/portable/ThirdParty/GCC/Posix/utils/wait_for_event.h"
  	"Source/portable/ThirdParty/GCC/Posix/utils/wait_for_event.c"
    "Source/portable/ThirdParty/GCC/Posix/port.c")
  else()
    message(FATAL_ERROR "Unkown port")
  endif()
endif()



# incude dirs
#interface include dirs need to contain the absolute path
set(INCLUDE_PUBLIC_DIRS "${CMAKE_CURRENT_LIST_DIR}/Source/include"
                        "${CMAKE_CURRENT_LIST_DIR}/CMSIS_RTOS"
                        "${CMAKE_CURRENT_LIST_DIR}/CMSIS/Include"
)



if(BUILD_TARGET)
  list(APPEND INCLUDE_PUBLIC_DIRS "${PROJECT_SOURCE_DIR}/Source/portable/GCC/ARM_CM4F")
  list(APPEND INCLUDE_PUBLIC_DIRS "${PROJECT_SOURCE_DIR}/app/cortex-m4f")
else()
  if(WIN32)
    list(APPEND INCLUDE_PUBLIC_DIRS "${PROJECT_SOURCE_DIR}/Source/portable/MSVC-MingW")
    list(APPEND INCLUDE_PUBLIC_DIRS "${PROJECT_SOURCE_DIR}/app/windows")
  elseif(UNIX)
    list(APPEND INCLUDE_PUBLIC_DIRS "${PROJECT_SOURCE_DIR}/Source/portable/ThirdParty/GCC/Posix")
    list(APPEND INCLUDE_PUBLIC_DIRS "${PROJECT_SOURCE_DIR}/Source/portable/ThirdParty/GCC/Posix/utils")
    list(APPEND INCLUDE_PUBLIC_DIRS "${PROJECT_SOURCE_DIR}/app/linux")
  else()
    message(FATAL_ERROR "You must provide a proper port for your compiler")
  endif()
endif()




set(INCLUDE_PRIVATE_DIRS "${CMAKE_CURRENT_LIST_DIR}/cpp11_gcc")



###########################
# add library
###########################
if(MODULE_SOURCES)
  set(module_name "FreeRTOS")
  # add files to library
  add_library(           "${module_name}"
  			              ${MODULE_SOURCES}) 

  if(BUILD_TARGET)
    target_compile_definitions("${module_name}" PUBLIC _GLIBCXX_HAS_GTHREADS)
  endif()

  target_compile_definitions(${module_name} PRIVATE $<$<C_COMPILER_ID:MSVC>:_CRT_SECURE_NO_WARNINGS>)
  target_compile_definitions(${module_name} PRIVATE $<$<CXX_COMPILER_ID:MSVC>:_CRT_SECURE_NO_WARNINGS>)

  

  if(BUILD_SIMULATION)
     target_compile_definitions(${module_name} 
       PRIVATE 
       $<$<COMPILE_LANGUAGE:C>:BUILD_SIMULATION>
       $<$<COMPILE_LANGUAGE:CXX>:BUILD_SIMULATION>
     )
  endif()

  target_compile_options(${module_name} PRIVATE 
    $<$<C_COMPILER_ID:MSVC>:/wd4133>
    $<$<C_COMPILER_ID:MSVC>:/wd4311>
    $<$<C_COMPILER_ID:MSVC>:/wd4312>
    $<$<C_COMPILER_ID:GNU>:-Wno-int-to-pointer-cast>
  )
  target_compile_options(${module_name} PRIVATE 
    $<$<CXX_COMPILER_ID:MSVC>:/wd4133>
    $<$<CXX_COMPILER_ID:MSVC>:/wd4311>
    $<$<CXX_COMPILER_ID:MSVC>:/wd4312>
    $<$<CXX_COMPILER_ID:GNU>:-Wno-int-to-pointer-cast>
  )


  target_include_directories("${module_name}"
                             PUBLIC 
                             "${INCLUDE_PUBLIC_DIRS}"
                             PRIVATE
                             "${INCLUDE_PRIVATE_DIRS}"
                             )
  
  if(UNIX)
    target_link_libraries("${module_name}"               
                         PUBLIC
                         pthread)
  endif()
  target_compile_definitions(${module_name} PUBLIC projCOVERAGE_TEST=0)
  if(CMAKE_COMPILER_IS_GNUCC OR GNU_GCC)
    #disable cast align warnings in this module ONLY (PRIVATE!)
    target_compile_options("${module_name}" PRIVATE -Wno-cast-align)
    target_compile_options("${module_name}" PRIVATE $<$<COMPILE_LANGUAGE:C>:-Wno-incompatible-pointer-types>)
    target_compile_options("${module_name}" PRIVATE $<$<COMPILE_LANGUAGE:C>:-Wno-pointer-to-int-cast>)
  endif() 
  ###########################
  # add tests
  ###########################
  #add_subdirectory("tests")
  
  FILE(GLOB FREERTOS_HEADER_FILES *.h)
  file(GLOB_RECURSE FREERTOS_HEADER_FILES RELATIVE ${CMAKE_SOURCE_DIR} "Source/include/*.h")
  if(WIN32)
    list(APPEND FREERTOS_HEADER_FILES "app/windows/FreeRTOSConfig.h" "Source/portable/MSVC-MingW/portmacro.h")
  endif()
  if(UNIX)
    list(APPEND FREERTOS_HEADER_FILES "app/linux/FreeRTOSConfig.h" "Source/portable/ThirdParty/GCC/Posix/portmacro.h" "Source/portable/ThirdParty/GCC/Posix/utils/wait_for_event.h")
  endif()
  if(BUILD_TARGET)
    list(APPEND FREERTOS_HEADER_FILES 
      "Source/portable/GCC/ARM_CM4F/portmacro.h"
      "app/cortex-m4f/FreeRTOSConfig.h"
    )
  endif()

  list(APPEND FREERTOS_HEADER_FILES 
    "CMSIS_RTOS/cmsis_os.h"
    "CMSIS/Include/cmsis_compiler.h"
    "CMSIS/Include/cmsis_gcc.h"
  )
  set_target_properties(${module_name} PROPERTIES PUBLIC_HEADER "${FREERTOS_HEADER_FILES}")

  install(TARGETS ${module_name} PUBLIC_HEADER DESTINATION "include/${module_name}")

endif() 
