// ◦ Xyz ◦

#include <WindowsManager.h>

bool Initialize();

bool CreateDeviceWGL(HDC& hDC, HGLRC& m_hRC, HWND& m_hWnd) {
    HDC hDc = ::GetDC(m_hWnd);
    PIXELFORMATDESCRIPTOR pfd = { 0 };
    pfd.nSize = sizeof(pfd);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 32;

    const int pf = ::ChoosePixelFormat(hDc, &pfd);
    if (pf == 0) {
        ::ReleaseDC(m_hWnd, hDc);
        return false;
    }
    if (::SetPixelFormat(hDc, pf, &pfd) == FALSE) {
        ::ReleaseDC(m_hWnd, hDc);
        return false;
    }
    ::ReleaseDC(m_hWnd, hDc);

    hDC = ::GetDC(m_hWnd);
    if (!m_hRC) {
        m_hRC = wglCreateContext(hDC);
    }
    return true;
}

void CleanupDeviceWGL(HDC& hDC, HWND& m_hWnd) {
    wglMakeCurrent(nullptr, nullptr);
    if (hDC) {
        ::ReleaseDC(m_hWnd, hDC);
        hDC = nullptr;
    }
}

LRESULT WINAPI WindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    WindowsManager* pThis = nullptr;
    if (msg == WM_NCCREATE) {
        CREATESTRUCT* pCreate = reinterpret_cast<CREATESTRUCT*>(lParam);
        pThis = reinterpret_cast<WindowsManager*>(pCreate->lpCreateParams);
        ::SetWindowLongPtrW(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pThis));
    }
    else {
        pThis = reinterpret_cast<WindowsManager*>(::GetWindowLongPtrW(hWnd, GWLP_USERDATA));
    }

    if (pThis) {
        if (pThis->Update(hWnd, msg, wParam, lParam)) {
            return true;
        }

        switch (msg) {
        case WM_SIZE:
            if (wParam != SIZE_MINIMIZED) {
                pThis->width = LOWORD(lParam);
                pThis->height = HIWORD(lParam);
            }
            return 0;
        case WM_SYSCOMMAND:
            if ((wParam & 0xfff0) == SC_KEYMENU) {
                return 0;
            }
            break;
        case WM_DESTROY:
            pThis->m_bRunning = false;
            ::PostQuitMessage(0);
            return 0;
        }
    }

    return ::DefWindowProcW(hWnd, msg, wParam, lParam);
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR, int nCmdShow)
{
    WindowsManager& windowsManager = WindowsManager::Instance();

    WNDCLASSW wc{};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = WindowsManager::CLASS_NAME;
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);

    if (!RegisterClassW(&wc))
    {
        MessageBoxW(nullptr, L"Не удалось зарегистрировать класс окна.", L"Ошибка", MB_OK | MB_ICONERROR);
        return 0;
    }

    HWND hwnd = CreateWindowExW(
        0,
        WindowsManager::CLASS_NAME,
        WindowsManager::TITLE,
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, WindowsManager::width, WindowsManager::height,
        nullptr,
        nullptr,
        hInstance,
        &windowsManager);

    if (!hwnd) {
        MessageBoxW(nullptr, L"Не удалось создать окно.", L"Ошибка", MB_OK | MB_ICONERROR);
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    HDC hDc{};
    HGLRC m_hRC = nullptr;

    if (!CreateDeviceWGL(hDc, m_hRC, hwnd)) {
        CleanupDeviceWGL(hDc, hwnd);
        ::DestroyWindow(hwnd);
        ::UnregisterClassW(WindowsManager::CLASS_NAME, GetModuleHandle(nullptr));
        return false;
    }
    wglMakeCurrent(hDc, m_hRC);

    windowsManager.Initialize(hwnd);
    Initialize();

    bool mainLoopLooped = true;
    MSG msg;
    {
        while (mainLoopLooped) {
            while (::PeekMessage(&msg, nullptr, 0U, 0U, PM_REMOVE)) {
                TranslateMessage(&msg);
                DispatchMessage(&msg);

                if (msg.message == WM_QUIT) {
                    mainLoopLooped = false;
                    break;
                }
            }

            if (::IsIconic(hwnd)) {
                ::Sleep(10);
                continue;
            }

            windowsManager.Render();
            ::SwapBuffers(hDc);
        }

        windowsManager.ShutDown();
        CleanupDeviceWGL(hDc, hwnd);

        if (m_hRC) {
            wglDeleteContext(m_hRC);
            m_hRC = nullptr;
        }
        ::DestroyWindow(hwnd);
        ::UnregisterClassW(WindowsManager::CLASS_NAME, GetModuleHandle(nullptr));
    }

    return static_cast<int>(msg.wParam);
}
