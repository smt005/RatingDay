#pragma once

#include <windows.h>
#include <GL/gl.h>
#include <string>
#include <vector>
#include <memory>

class Window {
public:
    using Uptr = std::unique_ptr<Window>;

public:
    Window() = delete;
    Window(std::string_view name)
        : _name(name)
    {};

    virtual ~Window() = default;
    virtual void Render() = 0;

    const std::string& GetName() const {
        return _name;
    }

private:
    const std::string _name;
};

class MainWindow {
public:
    MainWindow();
    ~MainWindow();

    bool Initialize();
    void Run();
    void Shutdown();

public:
    void AddWindow(Window::Uptr&& window);
    void RemoveWindow(std::string_view nameWindow);

private:
    bool CreateDeviceWGL();
    void CleanupDeviceWGL();

    void ProcessMessages();
    void Render();

    static LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

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

    std::vector<Window::Uptr> _windows;
};

