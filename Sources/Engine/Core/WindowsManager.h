#pragma once

#include <Windows.h>
#include <string>
#include <vector>
#include <map>
#include <memory>
#include "Singletone.h"

struct ImFont;

class Window {
public:
    using Ptr = std::shared_ptr<Window>;
    using Wptr = std::weak_ptr<Window>;

public:
    Window() = delete;
    Window(std::string_view name)
        : _name(name)
        , _visible(true)
        , _fullScreen(true)
    {};

    virtual ~Window() = default;
    virtual void Render() = 0;
    virtual void OnClose() {};

    const std::string& GetName() const {
        return _name;
    }

    bool IsVisible() const {
        return _visible;
    }

    void SetVisible(bool visible) {
        _visible = visible;
    }
    
    bool IsFullScreen() const {
        return _fullScreen;
    }

    void SetFullScreen(bool fullScreen) {
        _fullScreen = fullScreen;
    }

private:
    const std::string _name;
    bool _visible;
    bool _fullScreen;
};

class WindowsManager final : public Singletone<WindowsManager> {
public:
    WindowsManager() = default;
    ~WindowsManager() = default;

public:
    bool Initialize(HWND hWnd);
    void Render();
    void ShutDown();
    bool Update(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

public:
    Window::Wptr AddWindow(Window::Ptr window);
    void RemoveWindow(std::string_view nameWindow);

public:
    bool m_bRunning = false;
    bool m_bFullscreen = true;

public:
    inline static const wchar_t CLASS_NAME[] = L"RatingDayWindowClass";
    inline static const wchar_t TITLE[] = L"Rating day";
    static int width;
    static int height;
    static ImFont* GetFont(int size);

private:
    std::vector<Window::Ptr> _windows;
    static std::map<int, ImFont*> _largeFonts;
};

