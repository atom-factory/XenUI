// Author: Jake Rieger
// Created: 8/2/2024.
//

#include "Window.h"

namespace XenUI {
    Window::Window(
      HINSTANCE hInstance, int nCmdShow, int width, int height, LPCSTR className, LPCSTR title)
        : m_hWnd(nullptr), m_ClassName(className), m_Title(title), m_Width(width), m_Height(height),
          m_ShouldClose(false) {
        ThrowIfFailed(::CoInitializeEx(nullptr, COINIT_MULTITHREADED));

        if (RegisterWindowClass(hInstance) <= 0) {
            ThrowIfFailed(HRESULT_FROM_WIN32(GetLastError()));
        }

        InitializeInstance(hInstance, nCmdShow);
    }

    Window::~Window() {
        ::UnregisterClass(m_ClassName, GetModuleHandle(nullptr));
        ::DestroyWindow(m_hWnd);
        ::CoUninitialize();
    }

    void Window::SetTitle(const std::string& title) {
        ::SetWindowText(m_hWnd, title.c_str());
        m_Title = title.c_str();
    }

    void Window::SetSize(int width, int height) const {
        WINDOWPLACEMENT wp;
        ::GetWindowPlacement(m_hWnd, &wp);
        ::SetWindowPos(m_hWnd,
                       nullptr,
                       wp.rcNormalPosition.left,
                       wp.rcNormalPosition.top,
                       width,
                       height,
                       SWP_NOZORDER | SWP_NOACTIVATE);
    }

    void Window::SetPosition(int x, int y) const {
        RECT rc;
        ::GetClientRect(m_hWnd, &rc);
        ::SetWindowPos(m_hWnd, nullptr, x, y, rc.right, rc.bottom, SWP_NOZORDER | SWP_NOACTIVATE);
    }

    void Window::SetIcon(const char* icoFile) {}

    void Window::SetStyle(LONG style, LONG exStyle) const {
        ::SetWindowLong(m_hWnd, GWL_EXSTYLE, exStyle);
        ::SetWindowLong(m_hWnd, GWL_STYLE, style);
    }

    void Window::Minimize() const {
        ::ShowWindow(m_hWnd, SW_MINIMIZE);
    }

    void Window::Maximize() const {
        ::ShowWindow(m_hWnd, SW_MAXIMIZE);
    }

    void Window::Restore() const {
        ::ShowWindow(m_hWnd, SW_RESTORE);
    }

    void Window::TriggerRedraw() const {
        ::InvalidateRect(m_hWnd, nullptr, TRUE);
    }

    void Window::OnPaint() {}

    void Window::OnResize(int width, int height) {
        // ::UpdateWindow(m_hWnd);
    }

    LRESULT Window::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
        const LONG_PTR userData = ::GetWindowLongPtr(hWnd, GWLP_USERDATA);
        const auto window       = reinterpret_cast<Window*>(userData);

        if (!window) {
            return ::DefWindowProc(hWnd, uMsg, wParam, lParam);
        }

        switch (uMsg) {
            case WM_CLOSE: {
                window->m_ShouldClose = true;
                ::PostQuitMessage(0);
            }
                return 0;
            case WM_DESTROY:
                ::PostQuitMessage(0);
                break;
            case WM_SIZE: {
                const auto width  = LOWORD(lParam);
                const auto height = HIWORD(lParam);
                window->OnResize(width, height);
            } break;
            default:
                return ::DefWindowProc(hWnd, uMsg, wParam, lParam);
        }

        return 0;
    }

    ATOM Window::RegisterWindowClass(HINSTANCE hInstance) const {
        WNDCLASSEXA wc;
        ZeroMemory(&wc, sizeof(WNDCLASSEXA));

        wc.cbSize        = sizeof(WNDCLASSEXA);
        wc.style         = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
        wc.lpfnWndProc   = WndProc;
        wc.hInstance     = hInstance;
        wc.hIcon         = ::LoadIcon(hInstance, IDI_APPLICATION);
        wc.hCursor       = ::LoadCursor(nullptr, IDC_ARROW);
        wc.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1);
        wc.lpszClassName = m_ClassName;
        wc.hIconSm       = wc.hIcon;
        wc.cbWndExtra    = sizeof(Window);

        return RegisterClassExA(&wc);
    }

    void Window::InitializeInstance(HINSTANCE hInstance, int nCmdShow) {
        const int scrWidth  = ::GetSystemMetrics(SM_CXSCREEN);
        const int scrHeight = ::GetSystemMetrics(SM_CYSCREEN);
        const auto posX     = (scrWidth - m_Width) / 2;
        const auto posY     = (scrHeight - m_Height) / 2;

        m_hWnd = ::CreateWindowExA(0,
                                   m_ClassName,
                                   m_Title,
                                   WS_OVERLAPPEDWINDOW,
                                   posX,
                                   posY,
                                   m_Width,
                                   m_Height,
                                   nullptr,
                                   nullptr,
                                   hInstance,
                                   this);

        if (!m_hWnd) {
            ThrowIfFailed(HRESULT_FROM_WIN32(GetLastError()));
        }

        ::SetWindowLongPtr(m_hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));

        ::ShowWindow(m_hWnd, nCmdShow);
        ::UpdateWindow(m_hWnd);
    }

    void Window::DispatchMessages() {
        if (::PeekMessage(&m_Msg, nullptr, 0, 0, PM_REMOVE)) {
            ::TranslateMessage(&m_Msg);
            ::DispatchMessage(&m_Msg);
        }
    }
}  // namespace XenUI