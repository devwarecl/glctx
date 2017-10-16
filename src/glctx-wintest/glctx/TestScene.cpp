
#include "TestScene.hpp"

#include <Windows.h>
#include <GL/GL.h>

namespace glctx {
    class TestSceneImpl : public TestScene {
    public:
        virtual void render() override {
            glClearColor(0.2f, 0.3f, 0.8f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            glBegin(GL_TRIANGLES);
            glVertex3f(0.0f, 1.0f, 0.0f);
            glVertex3f(1.0f, -1.0f, 0.0f);
            glVertex3f(-1.0f, -1.0f, 0.0f);
            glEnd();

            glFlush();
        }
    };

    std::unique_ptr<TestScene> TestScene::New() {
        return std::make_unique<TestSceneImpl>();
    }
}
