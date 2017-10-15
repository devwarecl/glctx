
#include "ContextManagerWin.hpp"
#include "ContextWin.hpp"

#include <stdexcept>
#include <Windows.h>

namespace glctx {
    ContextManagerWin::ContextManagerWin() {}

    ContextManagerWin::~ContextManagerWin() {}

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
