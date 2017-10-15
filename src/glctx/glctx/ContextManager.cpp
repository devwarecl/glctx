
#include "ContextManager.hpp"

#if defined(WIN32)
#include "win/ContextManagerWin.hpp"
namespace glctx {
    typedef ContextManagerWin ContextManagerImpl;
}
#else 
#error "The current platform is not supported yet."
#endif

namespace glctx {
    ContextManager::ContextManager() {}

    ContextManager::~ContextManager() {}

    ContextManager* ContextManager::getInstance() {
        static ContextManagerImpl manager;
        return &manager;
    }
}
