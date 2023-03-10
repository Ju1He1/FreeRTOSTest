include(CMakePrintHelpers)

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)

# Without that flag CMake is not able to pass test compilation check
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

if(WIN32)
  set(COMPILER_EXE_SUFFIX ".exe")
else()
  set(COMPILER_EXE_SUFFIX "")
endif()
message("CMAKE_TOOLCHAIN_FILE is ${CMAKE_TOOLCHAIN_FILE}")

if(EXISTS ${BAREMETAL_ARM_TOOLCHAIN_PATH})
  message(STATUS "Cross compiler directory ${BAREMETAL_ARM_TOOLCHAIN_PATH} exists...")
else()
  # when this is called from conan ${BAREMETAL_ARM_TOOLCHAIN_PATH} is not available => search compiler in specified path from conan profile
  message(STATUS "Cross compiler directory (${BAREMETAL_ARM_TOOLCHAIN_PATH}) does not exist is it set in the Conan Profile?")
endif()

set(CMAKE_AR ${BAREMETAL_ARM_TOOLCHAIN_PATH}arm-none-eabi-ar${COMPILER_EXE_SUFFIX})
set(CMAKE_ASM_COMPILER ${BAREMETAL_ARM_TOOLCHAIN_PATH}arm-none-eabi-gcc${COMPILER_EXE_SUFFIX})
set(CMAKE_C_COMPILER ${BAREMETAL_ARM_TOOLCHAIN_PATH}arm-none-eabi-gcc${COMPILER_EXE_SUFFIX})
set(CMAKE_CXX_COMPILER ${BAREMETAL_ARM_TOOLCHAIN_PATH}arm-none-eabi-g++${COMPILER_EXE_SUFFIX})
set(CMAKE_LINKER ${BAREMETAL_ARM_TOOLCHAIN_PATH}arm-none-eabi-ld${COMPILER_EXE_SUFFIX})
set(CMAKE_OBJCOPY ${BAREMETAL_ARM_TOOLCHAIN_PATH}arm-none-eabi-objcopy${COMPILER_EXE_SUFFIX} CACHE INTERNAL "")
set(CMAKE_RANLIB ${BAREMETAL_ARM_TOOLCHAIN_PATH}arm-none-eabi-ranlib${COMPILER_EXE_SUFFIX} CACHE INTERNAL "")
set(CMAKE_SIZE ${BAREMETAL_ARM_TOOLCHAIN_PATH}arm-none-eabi-size${COMPILER_EXE_SUFFIX} CACHE INTERNAL "")
set(CMAKE_STRIP ${BAREMETAL_ARM_TOOLCHAIN_PATH}arm-none-eabi-strip${COMPILER_EXE_SUFFIX} CACHE INTERNAL "")

if(NOT COMPILER_ARCH_FLAGS)
  # Conan does not have access to the cached variables from CMakePresets.json => use settings from Env
  message(WARNING "COMPILER_ARCH_FLAGS not set.... are they set via the conan profile?")
else()
  message("COMPILER_ARCH_FLAGS exist. Value ${COMPILER_ARCH_FLAGS}")
endif()

set(CMAKE_C_FLAGS_INIT "${COMPILER_ARCH_FLAGS} -fdata-sections -ffunction-sections" CACHE INTERNAL "" FORCE)
set(CMAKE_CXX_FLAGS_INIT "${CMAKE_C_FLAGS_INIT} " CACHE INTERNAL "" FORCE)

# -Wl,--print-gc-sections will print all removed sections
set(CMAKE_EXE_LINKER_FLAGS_INIT "${LINKER_ARCH_FLAGS} -Wl,--gc-sections" CACHE INTERNAL "")

set(CMAKE_C_FLAGS_DEBUG_INIT "-Og -g" CACHE INTERNAL "")
set(CMAKE_C_FLAGS_RELEASE_INIT "-Os -DNDEBUG" CACHE INTERNAL "")
set(CMAKE_CXX_FLAGS_DEBUG_INIT "${CMAKE_C_FLAGS_DEBUG}" CACHE INTERNAL "")
set(CMAKE_CXX_FLAGS_RELEASE_INIT "${CMAKE_C_FLAGS_RELEASE}" CACHE INTERNAL "")

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

cmake_print_variables(CMAKE_C_FLAGS_DEBUG_INIT CMAKE_C_FLAGS_RELEASE_INIT CMAKE_CXX_FLAGS_DEBUG_INIT CMAKE_CXX_FLAGS_RELEASE_INIT)
