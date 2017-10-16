
#ifndef __glctx_context_hpp__
#define __glctx_context_hpp__

#include <cstdint>

namespace glctx {
    typedef std::uint64_t NativeHandle;

    struct ContextDesc {
        // OpenGL Version
        std::uint8_t versionMajor = 0;
        std::uint8_t versionMinor = 0;

        // compability profile flag
        bool compatibility = false;

        // double buffer?
        bool doubleBuffer = false;

        // framebuffer format
        std::uint8_t redBits = 0;
        std::uint8_t greenBits = 0;
        std::uint8_t blueBits = 0;
        std::uint8_t alphaBits = 0;

        std::uint8_t depthBits = 0;
    };

    /**
     * @brief An Graphics Library Context
     */
    class Context {
    public:
        virtual ~Context();

        virtual ContextDesc getDesc() const = 0;

        virtual NativeHandle getHandle() const = 0;

        virtual void makeCurrent() = 0;

        virtual void swapBuffers() = 0;
    };
}

#endif
