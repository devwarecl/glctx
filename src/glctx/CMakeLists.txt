set (target "glctx")

set (sources
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

add_library (${target} ${sources} ${sources_win})
