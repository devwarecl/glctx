
#ifndef __glctx_contextmanagerwin_hpp__
#define __glctx_contextmanagerwin_hpp__

#include "ContextManager.hpp"

namespace glctx {
    class ContextManagerWin : public ContextManager {
    public:
        ContextManagerWin();

        virtual ~ContextManagerWin();

        virtual void makeCurrent(Context* context) override;

        virtual Context* getCurrent() const override;

        virtual std::unique_ptr<Context> createContext(const NativeWindowHandle windowHandle, const ContextDesc &desc) override;
    };
}

#endif
