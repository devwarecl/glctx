
set (target "glctx")

set (sources
	"glctx/PreDef.hpp" 
	"glctx/Context.cpp" 
	"glctx/Context.hpp" 
	"glctx/ContextManager.cpp"
	"glctx/ContextManager.hpp" 
)

set (sources_win
	"glctx/win/ContextWin.cpp"
	"glctx/win/ContextWin.hpp" 
	"glctx/win/ContextManagerWin.cpp"
	"glctx/win/ContextManagerWin.hpp" 
)

source_group("\\glctx" FILES ${sources})
source_group("\\glctx\\win" FILES ${sources_win})

add_definitions(-DGLCTX_BUILD)

if (GLCTX_DYNAMIC)
	find_package(OpenGL REQUIRED)
    add_library (${target} SHARED ${sources} ${sources_win})
	target_link_libraries(${target} ${OPENGL_gl_LIBRARY})
else ()
    add_library (${target} ${sources} ${sources_win})
endif ()

set_target_properties (
	${target}
	PROPERTIES 
		DEBUG_OUTPUT_NAME ${target}d
		RELEASE_OUTPUT_NAME ${target}
)

install (TARGETS ${target} DESTINATION "lib")

install (
	DIRECTORY "${CMAKE_SOURCE_DIR}/src/${target}/glctx"
	DESTINATION "include"
	FILES_MATCHING PATTERN "*.hpp"
)
