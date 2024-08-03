#include "Core/Platform.h"
#include "Core/App.h"
#include "Core/Window.h"
#include "Core/Dimension.h"

#include <memory>

using namespace XenUI;

namespace {
    HINSTANCE g_hInst;
}  // namespace

/// This defines a simple button widget to display on screen.
/// You can define your own widgets like this or use any of the
/// built-in widgets found in`Widgets/`
class ButtonWidget final : public IWidget {
public:
    ButtonWidget() = default;
    void Draw(ID2D1RenderTarget* context, const Dimension& dim) override;
};

void ButtonWidget::Draw(ID2D1RenderTarget* context, const Dimension& dim) {
    ID2D1SolidColorBrush* brush = nullptr;
    XenUI::ThrowIfFailed(context->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::White), &brush));
    context->FillRectangle({100, 100, 300, 200}, brush);
    brush->Release();
}

class DemoApp final : public IApp {
public:
    DemoApp(int width, int height, const std::string& title) : XenUI::IApp(width, height, title) {
        m_pWindow->SetIcon("app.ico");
    }

    IWidget* BuildUI() override;
};

IWidget* DemoApp::BuildUI() {
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
