
#ifndef __glctx_context_hpp__
#define __glctx_context_hpp__

#include <cstdint>
#include <glctx/PreDef.hpp>

namespace glctx {
    typedef std::uint64_t NativeHandle;

    struct ContextDesc {
        struct {
            std::uint8_t major = 0;
            std::uint8_t minor = 0;
        } version;

        struct {
            std::uint8_t redBits = 0;
            std::uint8_t greenBits = 0;
            std::uint8_t blueBits = 0;
            std::uint8_t alphaBits = 0;
            std::uint8_t depthBits = 0;
            std::uint8_t stencilBits = 0;
        } framebuffer;

        struct {
            bool compatibility = false;
            bool doubleBuffer = false;
        } flags;

        static ContextDesc createCoreProfile() {
            return {
                {3, 3}, 
                {8, 8, 8, 8, 24, 8}, 
                {false, true}
            };
        }
    };

    /**
     * @brief An Graphics Library Context
     */
    class GLCTX_API Context {
    public:
        virtual ~Context();

        virtual ContextDesc getDesc() const = 0;

        virtual NativeHandle getHandle() const = 0;

        virtual void makeCurrent() = 0;

        virtual void swapBuffers() = 0;
    };
}

#endif
