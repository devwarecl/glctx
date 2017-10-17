
cmake_minimum_required (VERSION 3.0)

project (glctx)

option (GLCTX_TEST_PROGRAM "Include test program in the compilation process" OFF)
option (GLCTX_DYNAMIC "Build the DLL version of the library" OFF)

set (GLCTX_VERSION_MAJOR "0")
set (GLCTX_VERSION_MINOR "1")
set (GLCTX_VERSION_REVISION "0")

if (GLCTX_DYNAMIC)
    add_definitions("-DGLCTX_DYNAMIC")
endif ()

add_definitions("-DGLCTX_VERSION_MAJOR=${GLCTX_VERSION_MAJOR}")
add_definitions("-DGLCTX_VERSION_MINOR=${GLCTX_VERSION_MINOR}")
add_definitions("-DGLCTX_VERSION_REVISION=${GLCTX_VERSION_REVISION}")

include_directories("src/glctx")
add_subdirectory ("src/glctx")

if (GLCTX_TEST_PROGRAM)
    add_subdirectory ("src/glctx-wintest")
endif ()
