
#ifndef __glctx_contextmanager_hpp__
#define __glctx_contextmanager_hpp__

#include <cstdint>
#include <memory>

namespace glctx {
    struct ContextDesc;
    class Context;
    
    typedef std::uint64_t NativeWindowHandle;

    class ContextManager {
    public:
        static ContextManager* getInstance();

    public:
        virtual void makeCurrent(Context* context) = 0;
        virtual Context* getCurrent() const = 0;

        virtual std::unique_ptr<Context> createContext(const NativeWindowHandle windowHandle, const ContextDesc &desc) = 0;
    };
}

#endif
