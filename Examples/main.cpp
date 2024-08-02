#include "Platform.h"
#include "App.h"
#include "Window.h"

#include <memory>

namespace {
    HINSTANCE g_hInst;
}  // namespace

class DemoApp : public XenUI::IApp {
public:
    DemoApp(int width, int height, const std::string& title) : XenUI::IApp(width, height, title) {}
};

int WINAPI WinMain(_In_ HINSTANCE hInstance,
                   _In_opt_ HINSTANCE hPrevInstance,
                   _In_ LPSTR lpCmdLine,
                   _In_ int nCmdShow) {
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
    g_hInst = hInstance;

    DemoApp demoApp(800, 600, "XenUI Demo");
    demoApp.Run();

    return S_OK;
}
