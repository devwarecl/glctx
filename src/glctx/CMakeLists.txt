set (target "glctx")

set (sources
	"glctx/Context.cpp" 
	"glctx/Context.hpp" 
	"glctx/ContextManager.cpp"
	"glctx/ContextManager.hpp" 
	"glctx/ContextManagerWin.cpp"
	"glctx/ContextManagerWin.hpp" 
)

source_group("\\glctx" FILES ${sources})

add_library (${target} ${sources})
