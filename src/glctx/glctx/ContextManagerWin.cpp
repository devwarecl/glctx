
#include "ContextManagerWin.hpp"
#include "Context.hpp"

#include <stdexcept>
#include <Windows.h>

namespace glctx {
    class ContextWin : public Context {
    public:
        /**
         * @brief Create a owning OpenGL context with the specified features
         */
        explicit ContextWin(const HWND hWnd, const ContextDesc &desc) {
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

            m_hContext = ::wglCreateContext(hDC);

            if (!m_hContext) {
                throw std::runtime_error("Couldn't set the Pixel Format to the DC");
            }
        }

        virtual NativeHandle getHandle() const override {
            return reinterpret_cast<NativeHandle>(m_hContext);
        }

        virtual ContextDesc getDesc() const override {
            return m_desc;
        }

        virtual ~ContextWin() {

        }

    private:
        HGLRC m_hContext;
        ContextDesc m_desc;
    };

    ContextManagerWin::ContextManagerWin() {}

    ContextManagerWin::~ContextManagerWin() {}

    void ContextManagerWin::makeCurrent(Context* context) {

    }

    Context* ContextManagerWin::getCurrent() const {
        return nullptr;
    }

    std::unique_ptr<Context> ContextManagerWin::createContext(const NativeWindowHandle windowHandle, const ContextDesc &desc) {
        const HWND hWnd = reinterpret_cast<const HWND>(windowHandle);
        return std::make_unique<ContextWin>(hWnd, desc);
    }
}
