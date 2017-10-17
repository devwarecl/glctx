
#include "ContextWin.hpp"
#include <stdexcept>
#include <iostream>

#define WGL_CONTEXT_MAJOR_VERSION_ARB           0x2091
#define WGL_CONTEXT_MINOR_VERSION_ARB           0x2092
#define WGL_CONTEXT_LAYER_PLANE_ARB             0x2093
#define WGL_CONTEXT_FLAGS_ARB                   0x2094
#define WGL_CONTEXT_PROFILE_MASK_ARB            0x9126

#define WGL_CONTEXT_DEBUG_BIT_ARB               0x0001
#define WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB  0x0002

#define WGL_CONTEXT_CORE_PROFILE_BIT_ARB        0x00000001
#define WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB 0x00000002

namespace glctx {
    ContextWin::ContextWin(const HWND hWnd, const ContextDesc &desc) {
        // sanity validations
        if (! ::IsWindow(hWnd)) {
            throw std::runtime_error("ContextManagerWin::createContext: The supplied Window Handle is not a Window");
        }

        if (::GetDC(hWnd) == NULL) {
            throw std::runtime_error("Couldn't get a Device Context for the supplied window");
        }

        // prepare the context
        m_hWnd = hWnd;
        m_hDC = ::GetDC(hWnd);

        if (desc.compatibility) {
            this->setupCompatContext(desc);
        } else {
            this->setupCoreContext(desc);
        }
    }

    void ContextWin::setupCompatContext(const ContextDesc &desc) {
        PIXELFORMATDESCRIPTOR pfd = {
            sizeof(PIXELFORMATDESCRIPTOR),
	        1,
	        PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,    
	        PFD_TYPE_RGBA,          //The kind of framebuffer. RGBA or palette.
	        32,                     //Colordepth of the framebuffer.
	        0, 0, 0, 0, 0, 0,
	        0,
	        0,
	        0,
	        0, 0, 0, 0,
	        24,                     //Number of bits for the depthbuffer
	        8,                      //Number of bits for the stencilbuffer
	        0,                      //Number of Aux buffers in the framebuffer.
	        PFD_MAIN_PLANE,
	        0,
	        0, 0, 0
        };

        int pixelFormat = ::ChoosePixelFormat(m_hDC, &pfd);
        if (!pixelFormat) {
            throw std::runtime_error("Couldn't find a Pixel Format with the specified parameters");
        }

        if (!::SetPixelFormat(m_hDC, pixelFormat, &pfd)) {
            throw std::runtime_error("Couldn't set the Pixel Format to the DC");
        }

        m_hRC = ::wglCreateContext(m_hDC);

        if (!m_hRC) {
            throw std::runtime_error("Couldn't set the Pixel Format to the DC");
        }
    }

    void ContextWin::setupCoreContext(const ContextDesc &desc) {
        this->setupCompatContext(desc);
        this->makeCurrent();

        // I have a current context
        typedef HGLRC (*wglCreateContextAttribsARB_proc)(HDC, HGLRC, const int *);

        wglCreateContextAttribsARB_proc wglCreateContextAttribsARB;

        wglCreateContextAttribsARB = (wglCreateContextAttribsARB_proc)::wglGetProcAddress("wglCreateContextAttribsARB");
        if (!wglCreateContextAttribsARB) {
            throw std::runtime_error("Couldn't create a Core Profile context (missing wglCreateContextAttribsARB entry point)");
        }

        int contextAttribs[] = {
            WGL_CONTEXT_MAJOR_VERSION_ARB, desc.versionMajor,
            WGL_CONTEXT_MINOR_VERSION_ARB, desc.versionMinor,
            WGL_CONTEXT_PROFILE_MASK_ARB,
            WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
            WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
            0
        };

        HGLRC coreProfileContext = wglCreateContextAttribsARB(m_hDC, m_hRC, contextAttribs);
        if (!coreProfileContext) {
            throw std::runtime_error("Couldn't create a core context profile");
        }

        ::wglMakeCurrent(NULL, NULL);
        ::wglDeleteContext(m_hRC);

        m_hRC = coreProfileContext;
    }

    NativeHandle ContextWin::getHandle() const {
        return reinterpret_cast<NativeHandle>(m_hRC);
    }

    ContextDesc ContextWin::getDesc() const {
        return m_desc;
    }

    ContextWin::~ContextWin() {
        ::wglDeleteContext(m_hRC);
        m_hRC = NULL;
    }

    void ContextWin::makeCurrent() {
        if (!::wglMakeCurrent(m_hDC, m_hRC)) {
            throw std::runtime_error("ContextWin::makeCurrent: Couldn't make the current context");
        }
    }

    void ContextWin::swapBuffers() {
        ::SwapBuffers(m_hDC);
    }
}
