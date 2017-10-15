
#include "ContextWin.hpp"

#include <stdexcept>

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
        HDC hDC = ::GetDC(hWnd);

        PIXELFORMATDESCRIPTOR pfd = {
            sizeof(PIXELFORMATDESCRIPTOR),
	        1,
	        PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,    //Flags
	        PFD_TYPE_RGBA,            //The kind of framebuffer. RGBA or palette.
	        32,                        //Colordepth of the framebuffer.
	        0, 0, 0, 0, 0, 0,
	        0,
	        0,
	        0,
	        0, 0, 0, 0,
	        24,                        //Number of bits for the depthbuffer
	        8,                        //Number of bits for the stencilbuffer
	        0,                        //Number of Aux buffers in the framebuffer.
	        PFD_MAIN_PLANE,
	        0,
	        0, 0, 0
        };

        int pixelFormat = ::ChoosePixelFormat(hDC, &pfd);
        if (!pixelFormat) {
            throw std::runtime_error("Couldn't find a Pixel Format with the specified parameters");
        }

        if (!::SetPixelFormat(hDC, pixelFormat, &pfd)) {
            throw std::runtime_error("Couldn't set the Pixel Format to the DC");
        }

        m_hDC = hDC;
        m_hRC = ::wglCreateContext(hDC);

        if (!m_hRC) {
            throw std::runtime_error("Couldn't set the Pixel Format to the DC");
        }
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

    HGLRC ContextWin::getHGLRC() const {
        return m_hRC;
    }

    HDC ContextWin::getHDC() const {
        return m_hDC;
    }
}
