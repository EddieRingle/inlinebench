project(inlinebench C)

cmake_minimum_required(VERSION 3.0)

#
# Set up some variables
#

set(IB_ROOT_DIR "${PROJECT_SOURCE_DIR}")
set(IB_CONTRIB_DIR "${IB_ROOT_DIR}/contrib")
set(IB_SCRIPTS_DIR "${IB_ROOT_DIR}/scripts")
set(IB_OUT_DIR "${PROJECT_BINARY_DIR}/devroot")

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()

list(APPEND CMAKE_MODULE_PATH "${IB_SCRIPTS_DIR}/cmake/modules")

option(IB_BUILD_WITH_O0  "Build with -O0" OFF)
option(IB_BUILD_WITH_O2  "Build with -O2" OFF)
option(IB_BUILD_WITH_O3  "Build with -O3" OFF)
option(IB_BUILD_WITH_LTO "Build with Link-time Optimizations" OFF)

set(FORCE_STEP_DEFAULT "build")
if(CMAKE_CONFIGURATION_TYPES)
    set(FORCE_STEP_DEFAULT "configure")
endif()

set(FORCE_STEP ${FORCE_STEP_DEFAULT} CACHE STRING
    "Should the top level projects force configure/build/isntall each make"
)
set_property(CACHE FORCE_STEP PROPERTY STRINGS OFF configure build install)

if(FORCE_STEP STREQUAL configure)
    set(dependee "update")
elseif(FORCE_STEP STREQUAL build)
    set(dependee "configure")
elseif(FORCE_STEP STREQUAL install)
    set(dependee "build")
endif()

set(FORCE_STEP_ARGS
    DEPENDEES ${dependee}
    DEPENDERS ${FORCE_STEP}
)

#
# Modules/macros
#

include(ExternalProject2)
include(GroupByFolder)
include(HostMacros)
include(TargetArch)

#
# Host package detection
#

find_host_package(Git)

#
# Target Arch/OS detection
#

if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
        set(IB_TARGET_OS "darwin")
elseif(ANDROID)
        set(IB_TARGET_OS "android")
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
        set(IB_TARGET_OS "linux")
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
        set(IB_TARGET_OS "windows")
else()
        set(IB_TARGET_OS "${CMAKE_SYSTEM_NAME}")
endif()

target_architecture(IB_TARGET_ARCH)

set(IB_TARGET_OUT_DIR "${IB_OUT_DIR}/${IB_TARGET_OS}_${IB_TARGET_ARCH}")
set(IB_TARGET_GENERIC_OUT_DIR "${IB_OUT_DIR}/generic")
set(IB_TARGET_CONTRIB_OUT_DIR "${IB_TARGET_OUT_DIR}")

set(CMAKE_INSTALL_PREFIX ${IB_TARGET_OUT_DIR})

#
# Dependencies
#

include("${IB_CONTRIB_DIR}/CMakeLists.txt")

#
# inlinebench
#

include_directories(SYSTEM ${IB_TARGET_OUT_DIR}/include)
include_directories(SYSTEM ${IB_TARGET_GENERIC_OUT_DIR}/include)

set(inlinebench_PREFIX ${CMAKE_CURRENT_BINARY_DIR}/inlinebench)

set(inlinebench_CMAKE_ARGS
    -DCMAKE_INSTALL_PREFIX:PATH=<INSTALL_DIR>
    -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    -DCMAKE_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN_FILE}
    -DCMAKE_OSX_ARCHITECTURES=${CMAKE_OSX_ARCHITECTURES}
    -DCMAKE_PREFIX_PATH=${IB_TARGET_OUT_DIR}
    -DIB_BUILD_WITH_O0=${IB_BUILD_WITH_O0}
    -DIB_BUILD_WITH_O2=${IB_BUILD_WITH_O2}
    -DIB_BUILD_WITH_O3=${IB_BUILD_WITH_O3}
    -DIB_BUILD_WITH_LTO=${IB_BUILD_WITH_LTO}
    -Wno-dev
)

ExternalProject_Add(inlinebench
    CMAKE_ARGS  ${inlinebench_CMAKE_ARGS}
    SOURCE_DIR  ${IB_ROOT_DIR}/inlinebench
    INSTALL_DIR ${IB_TARGET_OUT_DIR}
)
if(FORCE_STEP)
    ExternalProject_Add_Step(inlinebench forcebuild
        COMMAND ${CMAKE_COMMAND} -E echo "Force build of inlinebench"
        ${FORCE_STEP_ARGS}
        ALWAYS 1
    )
endif()

add_dependencies(inlinebench libtime)

add_custom_command(TARGET inlinebench PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E create_symlink ${IB_TARGET_OUT_DIR} ${IB_TARGET_GENERIC_OUT_DIR}
    COMMENT "Symlinking fallback include path..."
)
