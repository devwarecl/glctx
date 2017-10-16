
#ifndef __glctx_testscene_hpp__
#define __glctx_testscene_hpp__

#include <memory>

namespace glctx {
    class TestScene {
    public:
        TestScene() {}

        virtual ~TestScene() {}

        virtual void render() = 0;

    public:
        static std::unique_ptr<TestScene> New();
    };
}

#endif
