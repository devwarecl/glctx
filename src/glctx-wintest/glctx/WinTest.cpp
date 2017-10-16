
#include <Windows.h>
#include <GL/GL.h>

#include <glctx/Context.hpp>
#include <glctx/ContextManager.hpp>

#include "TestScene.hpp"

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_CLOSE:
        ::PostMessage(hWnd, 0, 0, WM_QUIT);
        return 0;
    }

    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

int main() {
    const auto CLASS_NAME = TEXT("MyWindow");
    const auto WINDOW_TITLE = TEXT("My OpenGL Window!");

    const HINSTANCE hInstance = ::GetModuleHandle(NULL);

    WNDCLASS wc = {};

    wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    wc.hCursor = ::LoadCursor(NULL, IDC_ARROW);
    wc.hIcon = ::LoadIcon(NULL, IDI_APPLICATION);
    wc.hInstance = hInstance;
    wc.lpfnWndProc = WndProc;
    wc.lpszClassName = CLASS_NAME;

    ::RegisterClass(&wc);

    HWND hWnd = ::CreateWindow (
        CLASS_NAME, 
        WINDOW_TITLE, 
        WS_OVERLAPPEDWINDOW, 
        CW_USEDEFAULT, CW_USEDEFAULT, 
        640, 480, 
        NULL, NULL, hInstance, NULL
    );

    ::ShowWindow(hWnd, SW_SHOW);
    ::UpdateWindow(hWnd);

    // at this point, create the opengl context
    const glctx::NativeWindowHandle handle = reinterpret_cast<glctx::NativeWindowHandle>(hWnd);
    const glctx::ContextDesc desc = {
        3, 3, 
        false, 
        true, 
        8, 8, 8, 0
    };
    
    glctx::ContextManager *contextManager = glctx::ContextManager::getInstance();
    glctx::Context *context = contextManager->createContext(handle, desc);
    context->makeCurrent();

    auto scene = glctx::TestScene::New();

    MSG msg = {};

    bool running = true;

    while (running) {
        if (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            if (msg.message == WM_QUIT) {
                running = false;
            } else {
                ::TranslateMessage(&msg);
                ::DispatchMessage(&msg);
            }
        } else {
            scene->render();
            context->swapBuffers();
        }
    }

    scene.release();

    contextManager->destroyContext(context);

    ::DestroyWindow(hWnd);
    ::UnregisterClass(CLASS_NAME, hInstance);

    return 0;
}
