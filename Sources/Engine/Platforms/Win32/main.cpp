// ◦ Xyz ◦

#include <windows.h>
#include <WindowsManager.h>

#include <GL/gl.h>
#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_opengl3.h"

const wchar_t CLASS_NAME[] = L"BasicWindowClass";
const int width = 400;
const int height = 600;
WindowsManager windowsManager;

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

bool Initialize(WindowsManager& windowsManager);

void OnClose(WindowsManager& windowsManager);


//Forward declare message handler from imgui_impl_win32.cpp
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

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

    if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam)) {
        return true;
    }

    if (pThis) {
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
    WNDCLASSW wc{};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);

    if (!RegisterClassW(&wc))
    {
        MessageBoxW(nullptr, L"Не удалось зарегистрировать класс окна.", L"Ошибка", MB_OK | MB_ICONERROR);
        return 0;
    }

    HWND hwnd = CreateWindowExW(
        0,
        CLASS_NAME,
        L"Тест",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, width, height,
        nullptr,
        nullptr,
        hInstance,
        &windowsManager);

    if (!hwnd)
    {
        MessageBoxW(nullptr, L"Не удалось создать окно.", L"Ошибка", MB_OK | MB_ICONERROR);
        return 0;
    }

    HDC hDc{};
    HGLRC m_hRC = nullptr;

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    { // Инициализация OpenGL
        if (!CreateDeviceWGL(hDc, m_hRC, hwnd)) {
            CleanupDeviceWGL(hDc, hwnd);
            ::DestroyWindow(hwnd);
            ::UnregisterClassW(L"RatingDayWindowClass", GetModuleHandle(nullptr));
            return false;
        }
        wglMakeCurrent(hDc, m_hRC);
    }

    // Инициализация ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

    // Установка стиля ImGui
    ImGui::StyleColorsDark();

    // Инициализация Platform и Renderer backends для ImGui
    ImGui_ImplWin32_InitForOpenGL(hwnd);
    ImGui_ImplOpenGL3_Init();

    Initialize(windowsManager);
    bool running = true;

    MSG msg{};
    {
        while (running) {
            //while (GetMessage(&msg, nullptr, 0, 0)) {
            while (::PeekMessage(&msg, nullptr, 0U, 0U, PM_REMOVE)) {
                TranslateMessage(&msg);
                DispatchMessage(&msg);

                if (msg.message == WM_QUIT) {
                    running = false;
                    break;
                }
            }

            if (::IsIconic(hwnd)) {
                ::Sleep(10);
                continue;
            }

            // Начало нового кадра ImGui
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplWin32_NewFrame();
            ImGui::NewFrame();

            windowsManager.Render();

            // Завершение кадра
            ImGui::Render();
            glViewport(0, 0, width, height);
            glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
            glClear(GL_COLOR_BUFFER_BIT);
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            // Презентация кадра
            ::SwapBuffers(hDc);
        }

        {
            if (hwnd != nullptr) {
                ImGui_ImplOpenGL3_Shutdown();
                ImGui_ImplWin32_Shutdown();
                ImGui::DestroyContext();
                CleanupDeviceWGL(hDc, hwnd);
                if (m_hRC) {
                    wglDeleteContext(m_hRC);
                    m_hRC = nullptr;
                }
                ::DestroyWindow(hwnd);
                ::UnregisterClassW(L"RatingDayWindowClass", GetModuleHandle(nullptr));
                hwnd = nullptr;
            }
        }
    }

    return static_cast<int>(msg.wParam);
}
