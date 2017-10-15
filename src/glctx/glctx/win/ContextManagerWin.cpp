
#include "ContextManagerWin.hpp"

#include <stdexcept>
#include <Windows.h>

namespace glctx {
    ContextManagerWin::ContextManagerWin() {}

    ContextManagerWin::~ContextManagerWin() {}

    void ContextManagerWin::makeCurrent(Context* context_) {
        auto context = dynamic_cast<ContextWin*>(context_);

        HDC hDC = NULL;
        HGLRC hRC = NULL;
        
        if (context) {
            hDC = context->getHDC();
            hRC = context->getHGLRC();
        }

        ::wglMakeCurrent(hDC, hRC);
    }

    Context* ContextManagerWin::getCurrent() const {
        return nullptr;
    }

    Context* ContextManagerWin::createContext(const NativeWindowHandle windowHandle, const ContextDesc &desc) {
        const HWND hWnd = reinterpret_cast<const HWND>(windowHandle);
        return new ContextWin(hWnd, desc);
    }

    void ContextManagerWin::destroyContext(Context *context) {
        if (context) {
            delete context;
        }
    }
}
