
#ifndef __glctx_contextmanagerwin_hpp__
#define __glctx_contextmanagerwin_hpp__

#include <glctx/ContextManager.hpp>

#include <vector>
#include <memory>

namespace glctx {
    class ContextWin;
    class ContextManagerWin : public ContextManager {
    public:
        ContextManagerWin();

        virtual ~ContextManagerWin();

        virtual Context* createContext(const NativeWindowHandle windowHandle, const ContextDesc &desc) override;

        virtual void destroyContext(Context *context) override;

    private:
        std::vector<std::unique_ptr<ContextWin>> m_contexts;
    };
}

#endif
