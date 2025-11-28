#pragma once

#include <string>
#include <vector>
#include <map>
#include <memory>

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

class AppWindow {
public:
    AppWindow();
    ~AppWindow();

    bool Initialize();
    void Run();
    void Shutdown();

public:
    Window::Wptr AddWindow(Window::Ptr window);
    void RemoveWindow(std::string_view nameWindow);

//private:
    bool CreateDeviceWGL();
    void CleanupDeviceWGL();

    void ProcessMessages();
    void Render();

public:
    bool m_bRunning = false;
    bool m_bFullscreen = true;

public:
    static int width;
    static int height;
    static ImFont* GetFont(int size);

private:
    std::vector<Window::Ptr> _windows;
    static std::map<int, ImFont*> _largeFonts;
};

