#pragma once

#include <windows.h>
#include <GL/gl.h>

class MainWindow {
public:
    MainWindow();
    ~MainWindow();

    bool Initialize();
    void Run();
    void Shutdown();

private:
    HWND m_hWnd;
    bool m_bRunning;

    // OpenGL
    HDC m_hDC;
    HGLRC m_hRC;
    int m_width;
    int m_height;

    struct WGL_WindowData {
        HDC hDC;
    } m_wglData;

    bool CreateDeviceWGL();
    void CleanupDeviceWGL();

    static LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
    void ProcessMessages();
    void Render();
};

