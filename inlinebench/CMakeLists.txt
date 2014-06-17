cmake_minimum_required(VERSION 3.0)

find_package(libtime NO_MODULE REQUIRED)

set(inlinebench_SRCS
    src/inlinebench.c
    src/maths.c
)

option(IB_BUILD_WITH_O0  "Build with -O0" OFF)
option(IB_BUILD_WITH_O2  "Build with -O2" OFF)
option(IB_BUILD_WITH_O3  "Build with -O3" OFF)
option(IB_BUILD_WITH_LTO "Build with Link-time Optimizations" OFF)

set(inlinebench_CFLAGS -std=c11 -Wall -Werror)
if(IB_BUILD_WITH_O0)
    set(inlinebench_CFLAGS
        ${inlinebench_CFLAGS}
        -O0
    )
    message(STATUS "Building with -O0")
elseif(IB_BUILD_WITH_O2)
    set(inlinebench_CFLAGS
        ${inlinebench_CFLAGS}
        -O2
    )
    message(STATUS "Building with -O2")
elseif(IB_BUILD_WITH_O3)
    set(inlinebench_CFLAGS
        ${inlinebench_CFLAGS}
        -O3
    )
    message(STATUS "Building with -O3")
endif()
if(IB_BUILD_WITH_LTO)
    set(inlinebench_CFLAGS
        ${inlinebench_CFLAGS}
        -flto
    )
    message(STATUS "Building with -flto")
endif()

add_executable(inlinebench ${inlinebench_SRCS})

target_include_directories(inlinebench
    SYSTEM PRIVATE time
    SYSTEM PRIVATE ${CMAKE_INSTALL_PREFIX}/include
)

target_link_libraries(inlinebench
    time
)

target_compile_options(inlinebench
    PRIVATE ${inlinebench_CFLAGS}
)

install(TARGETS inlinebench
        RUNTIME DESTINATION bin
)
