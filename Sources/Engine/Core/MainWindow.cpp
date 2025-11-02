#include "MainWindow.h"
#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_opengl3.h"
#include <windows.h>
#include <GL/gl.h>

// Forward declare message handler from imgui_impl_win32.cpp
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

MainWindow::MainWindow() 
    : m_hWnd(nullptr)
    , m_bRunning(false)
    , m_hDC(nullptr)
    , m_hRC(nullptr)
    , m_width(1280)
    , m_height(800)
{
}

MainWindow::~MainWindow() {
    Shutdown();
}

bool MainWindow::Initialize() {
    // Включение DPI awareness
    //ImGui_ImplWin32_EnableDpiAwareness(); // FIXME: Doesn't work with Win32+OpenGL

    // Регистрация класса окна (CS_OWNDC для OpenGL)
    WNDCLASSEXW wc = { 
        sizeof(wc), 
        CS_OWNDC, 
        WndProc, 
        0L, 
        0L, 
        GetModuleHandle(nullptr), 
        nullptr, 
        nullptr, 
        nullptr, 
        nullptr, 
        L"RatingDayWindowClass", 
        nullptr 
    };
    ::RegisterClassExW(&wc);

    // Создание окна
    m_hWnd = ::CreateWindowW(
        wc.lpszClassName,
        L"RatingDay",
        WS_OVERLAPPEDWINDOW,
        100, 100, 
        1280, 800,
        nullptr, 
        nullptr, 
        wc.hInstance, 
        this
    );

    if (m_hWnd == nullptr) {
        return false;
    }

    // Сохранение указателя на экземпляр в данных окна
    ::SetWindowLongPtrW(m_hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));

    // Инициализация OpenGL
    if (!CreateDeviceWGL()) {
        CleanupDeviceWGL();
        ::DestroyWindow(m_hWnd);
        ::UnregisterClassW(L"RatingDayWindowClass", GetModuleHandle(nullptr));
        return false;
    }
    wglMakeCurrent(m_wglData.hDC, m_hRC);

    // Показ окна
    ::ShowWindow(m_hWnd, SW_SHOWDEFAULT);
    ::UpdateWindow(m_hWnd);

    // Инициализация ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

    // Установка стиля ImGui
    ImGui::StyleColorsDark();

    // Инициализация Platform и Renderer backends для ImGui
    ImGui_ImplWin32_InitForOpenGL(m_hWnd);
    ImGui_ImplOpenGL3_Init();

    m_bRunning = true;
    return true;
}

void MainWindow::Run() {
    MSG msg = {};
    while (m_bRunning) {
        // Обработка сообщений Windows
        while (::PeekMessage(&msg, nullptr, 0U, 0U, PM_REMOVE)) {
            ::TranslateMessage(&msg);
            ::DispatchMessage(&msg);
            if (msg.message == WM_QUIT) {
                m_bRunning = false;
            }
        }

        if (!m_bRunning) {
            break;
        }

        if (::IsIconic(m_hWnd)) {
            ::Sleep(10);
            continue;
        }

        // Начало нового кадра ImGui
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();

        // Рендеринг
        Render();

        // Завершение кадра
        ImGui::Render();
        glViewport(0, 0, m_width, m_height);
        glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // Презентация кадра
        ::SwapBuffers(m_wglData.hDC);
    }
}

void MainWindow::Render() {
    // Простое окно ImGui
    ImGui::Begin("Main Window");
    ImGui::Text("RatingDay Application");
    ImGui::Text("This is a sample window.");
    if (ImGui::Button("Close")) {
        m_bRunning = false;
    }
    ImGui::End();
}

void MainWindow::Shutdown() {
    if (m_hWnd != nullptr) {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplWin32_Shutdown();
        ImGui::DestroyContext();
        CleanupDeviceWGL();
        if (m_hRC) {
            wglDeleteContext(m_hRC);
            m_hRC = nullptr;
        }
        ::DestroyWindow(m_hWnd);
        ::UnregisterClassW(L"RatingDayWindowClass", GetModuleHandle(nullptr));
        m_hWnd = nullptr;
    }
}

LRESULT WINAPI MainWindow::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    MainWindow* pThis = nullptr;
    if (msg == WM_NCCREATE) {
        CREATESTRUCT* pCreate = reinterpret_cast<CREATESTRUCT*>(lParam);
        pThis = reinterpret_cast<MainWindow*>(pCreate->lpCreateParams);
        ::SetWindowLongPtrW(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pThis));
    } else {
        pThis = reinterpret_cast<MainWindow*>(::GetWindowLongPtrW(hWnd, GWLP_USERDATA));
    }

    if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam)) {
        return true;
    }

    if (pThis) {
        switch (msg) {
        case WM_SIZE:
            if (wParam != SIZE_MINIMIZED) {
                pThis->m_width = LOWORD(lParam);
                pThis->m_height = HIWORD(lParam);
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

bool MainWindow::CreateDeviceWGL() {
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

    m_wglData.hDC = ::GetDC(m_hWnd);
    if (!m_hRC) {
        m_hRC = wglCreateContext(m_wglData.hDC);
    }
    return true;
}

void MainWindow::CleanupDeviceWGL() {
    wglMakeCurrent(nullptr, nullptr);
    if (m_wglData.hDC) {
        ::ReleaseDC(m_hWnd, m_wglData.hDC);
        m_wglData.hDC = nullptr;
    }
}

