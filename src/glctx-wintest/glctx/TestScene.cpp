
#include "TestScene.hpp"

#include <iostream>
#include <Windows.h>
#include <GL/GL.h>

namespace glctx {
    class TestSceneImpl : public TestScene {
    public:
        TestSceneImpl() {
            std::cout << ::glGetString(GL_VERSION) << std::endl;
        }

        virtual void render() override {
            glClearColor(0.2f, 0.3f, 0.8f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            glFlush();
        }

    private:

    };

    std::unique_ptr<TestScene> TestScene::New() {
        return std::make_unique<TestSceneImpl>();
    }
}
