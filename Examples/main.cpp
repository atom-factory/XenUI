#include "Platform.h"
#include "App.h"
#include "Window.h"

#include <memory>

namespace {
    HINSTANCE g_hInst;
}  // namespace

namespace {
    std::unique_ptr<XenUI::App> g_App;
}

int WINAPI WinMain(_In_ HINSTANCE hInstance,
                   _In_opt_ HINSTANCE hPrevInstance,
                   _In_ LPSTR lpCmdLine,
                   _In_ int nCmdShow) {
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
    g_hInst = hInstance;

    XenUI::Window window(hInstance, nCmdShow, 800, 600);
    window.SetTitle("XenUI Demo");
    window.Show();

    return S_OK;
}
