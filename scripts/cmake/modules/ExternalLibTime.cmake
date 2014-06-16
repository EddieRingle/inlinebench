include(ExternalProject2)

set(libtime_PREFIX ${CMAKE_CURRENT_BINARY_DIR}/libtime)

set(libtime_CMAKE_ARGS
    -DCMAKE_INSTALL_PREFIX:PATH=<INSTALL_DIR>
    -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    -DCMAKE_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN_FILE}
    -DCMAKE_OSX_ARCHITECTURES=${CMAKE_OSX_ARCHITECTURES}
    -DCMAKE_PREFIX_PATH=${IB_TARGET_CONTRIB_OUT_DIR}
    -Wno-dev
)

ExternalProject_Add(libtime
    PREFIX ${libtime_PREFIX}

    GIT_REPOSITORY git://github.com/tycho/libtime.git

    PATCH_COMMAND ${CMAKE_COMMAND} -E copy_if_different ${IB_SCRIPTS_DIR}/cmake/modules/libtime.cmake <SOURCE_DIR>/CMakeLists.txt

    INSTALL_DIR ${IB_TARGET_CONTRIB_OUT_DIR}
    CMAKE_ARGS ${libtime_CMAKE_ARGS}
)
