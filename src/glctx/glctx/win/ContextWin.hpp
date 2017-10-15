
#ifndef __glctx_contextwin_hpp__
#define __glctx_contextwin_hpp__

#include <Windows.h>
#include <glctx/Context.hpp>

namespace glctx {
    class ContextWin : public Context {
    public:
        /**
         * @brief Create a owning OpenGL context with the specified features
         */
        explicit ContextWin(const HWND hWnd, const ContextDesc &desc);

        virtual NativeHandle getHandle() const override;

        virtual ContextDesc getDesc() const override;

        virtual void makeCurrent() override;

        virtual ~ContextWin();

        HGLRC getHGLRC() const;

        HDC getHDC() const;

    private:
        HWND m_hWnd = NULL;
        HGLRC m_hRC = NULL;
        HDC m_hDC = NULL;
        ContextDesc m_desc;
    };
}

#endif
