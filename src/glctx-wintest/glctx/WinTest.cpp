
#include <Windows.h>

#include <glctx/ContextManager.hpp>

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

int main() {
    const auto CLASS_NAME = TEXT("MyWindow");
    const auto WINDOW_TITLE = TEXT("My OpenGL Window!");

    const HINSTANCE hInstance = ::GetModuleHandle(NULL);

    WNDCLASS wc = {};

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

    MSG msg = {};

    while(GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    ::DestroyWindow(hWnd);
    ::UnregisterClass(CLASS_NAME, hInstance);

    return 0;
}
