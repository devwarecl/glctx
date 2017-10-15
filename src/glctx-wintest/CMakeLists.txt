
set (target "glctx-wintest")
set (sources "glctx/WinTest.cpp")

include_directories(".")

source_group("\\glctx" FILES ${sources})

add_executable (${target} ${sources})

target_link_libraries(${target} glctx opengl32)
