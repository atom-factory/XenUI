#include "Platform.h"
#include "App.h"
#include "Window.h"

#include <memory>

namespace {
    HINSTANCE g_hInst;
}  // namespace

class ButtonWidget : public XenUI::IWidget {
public:
    ButtonWidget() = default;
    void Draw(ID2D1RenderTarget* context) override;
};

void ButtonWidget::Draw(ID2D1RenderTarget* context) {
    ID2D1SolidColorBrush* brush = nullptr;
    XenUI::ThrowIfFailed(context->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::White), &brush));
    context->FillRectangle({100, 100, 300, 200}, brush);
    brush->Release();
}

class DemoApp final : public XenUI::IApp {
public:
    DemoApp(int width, int height, const std::string& title) : XenUI::IApp(width, height, title) {}
    XenUI::IWidget* BuildUI() override;
};

XenUI::IWidget* DemoApp::BuildUI() {
    return new ButtonWidget();
}

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
