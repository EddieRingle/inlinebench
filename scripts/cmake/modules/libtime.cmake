project(libtime C)

cmake_minimum_required(VERSION 3.0)

if(NOT CMAKE_BUILD_TYPE)
        set(CMAKE_BUILD_TYPE "Release")
endif()

#
# Source files
#

set(libtime_SRCS
    src/libtime.c
)

#
# Private header files
#

set(libtime_HDRS
    private/platform.h
)
if(MSVC)
    set(libtime_HDRS
        ${libtime_HDRS}

        private/inttypes.h
        private/stdint.h
    )
endif()

#
# Public header files
#

set(libtime_APIS
    include/libtime.h
)

#
# Flags
#

set(libtime_CFLAGS     -std=gnu11 -fno-strict-aliasing -Wall -Werror)
set(libtime_CFOPTIMIZE -O2)
if(APPLE)
    set(libtime_CFLAGS "${libtime_CFLAGS} -Wa,-q")
endif()

#
# libtime
#

add_library(time STATIC ${libtime_SRCS})

if(UNIX)
    target_link_libraries(time m)
endif()

target_include_directories(time
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include/libtime>
    PRIVATE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/private>
)

target_compile_options(time
    PRIVATE ${libtime_CFOPTIMIZE} ${libtime_CFLAGS}
)

install(TARGETS time EXPORT libtimeConfig
    ARCHIVE DESTINATION lib
)

install(EXPORT libtimeConfig
    DESTINATION lib/cmake/libtime
)

install(FILES ${libtime_APIS} DESTINATION include/libtime)
