#include "XenUI.h"
#include "XenApp.h"

#include <memory>
#include <stdexcept>

namespace {
    HINSTANCE g_hInst;
    HWND g_hWnd;

    constexpr int kDefaultWidth  = 800;
    constexpr int kDefaultHeight = 600;
    LPCSTR kClassName            = "XenDemoWindowClass";
    LPCSTR kWindowName           = "XenUI Demo";
}  // namespace

namespace {
    std::string GetErrorMessage(HRESULT hr) {
        char* errorMsg = nullptr;
        FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM |
                         FORMAT_MESSAGE_IGNORE_INSERTS,
                       nullptr,
                       hr,
                       MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                       (LPSTR)&errorMsg,
                       0,
                       nullptr);

        std::string errorString;
        if (errorMsg) {
            errorString = errorMsg;
            LocalFree(errorMsg);
        } else {
            errorString = "Unknown error";
        }

        return errorString;
    }

    void ThrowIfFailed(HRESULT hr) {
        if (FAILED(hr)) {
            throw std::runtime_error(GetErrorMessage(hr));
        }
    }
}  // namespace

ATOM RegisterWindowClass(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE, int);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void EventLoop(HWND hWnd);

namespace {
    std::unique_ptr<XenUI::XenApp> g_App;
}

int WINAPI WinMain(_In_ HINSTANCE hInstance,
                   _In_opt_ HINSTANCE hPrevInstance,
                   _In_ LPSTR lpCmdLine,
                   _In_ int nCmdShow) {
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
    g_hInst = hInstance;

    // Initialize the COM API
    ThrowIfFailed(::CoInitializeEx(nullptr, COINIT_MULTITHREADED));

    if (RegisterWindowClass(hInstance) <= 0) {
        return E_FAIL;
    }

    if (!InitInstance(hInstance, nCmdShow)) {
        return E_FAIL;
    }

    g_App = std::make_unique<XenUI::XenApp>(g_hWnd);
    EventLoop(g_hWnd);

    ::CoUninitialize();

    return S_OK;
}

void EventLoop(HWND hWnd) {
    MSG msg = {};
    while (WM_QUIT != msg.message) {
        if (::PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
            ::TranslateMessage(&msg);
            ::DispatchMessage(&msg);
        }
    }
}

ATOM RegisterWindowClass(HINSTANCE hInstance) {
    WNDCLASSEXA wc = {};
    ZeroMemory(&wc, sizeof(wc));
    wc.cbSize        = sizeof(WNDCLASSEXA);
    wc.style         = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
    wc.lpfnWndProc   = WndProc;
    wc.hInstance     = hInstance;
    wc.hIcon         = ::LoadIcon(hInstance, IDI_APPLICATION);
    wc.hCursor       = ::LoadCursor(nullptr, IDC_ARROW);
    wc.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1);
    wc.lpszClassName = kClassName;
    wc.hIconSm       = wc.hIcon;

    return ::RegisterClassExA(&wc);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow) {
    const int scrWidth  = ::GetSystemMetrics(SM_CXSCREEN);
    const int scrHeight = ::GetSystemMetrics(SM_CYSCREEN);
    const auto posX     = (scrWidth - kDefaultWidth) / 2;
    const auto posY     = (scrHeight - kDefaultHeight) / 2;

    g_hWnd = ::CreateWindowExA(0,
                               kClassName,
                               kWindowName,
                               WS_OVERLAPPEDWINDOW,
                               posX,
                               posY,
                               kDefaultWidth,
                               kDefaultHeight,
                               nullptr,
                               nullptr,
                               hInstance,
                               nullptr);

    if (!g_hWnd) {
        return FALSE;
    }

    ::UpdateWindow(g_hWnd);
    ::ShowWindow(g_hWnd, nCmdShow);

    return TRUE;
}

LRESULT WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_DESTROY:
            ::PostQuitMessage(0);
            break;
        case WM_CLOSE:
            ::DestroyWindow(g_hWnd);
            ::PostQuitMessage(0);
            break;
        default:
            return ::DefWindowProc(hWnd, uMsg, wParam, lParam);
    }

    return 0;
}
