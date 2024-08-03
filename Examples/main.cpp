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
/// built-in widgets found in `Widgets/`
class ButtonWidget final : public IWidget {
public:
    using IWidget::IWidget;
    void Draw(Context* context, const Dimension& dim) override;
};

void ButtonWidget::Draw(Context* context, const Dimension& dim) {
    const auto brush = context->CreateColorBrush(Colors::Cyan);
    context->GetD2DRenderTarget()->FillRectangle(GetRect().ToD2DRect(), brush);
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
    const auto dim = m_pCanvas->GetDimension();

    const auto helloBtn = new ButtonWidget({dim.Width(20.f), dim.Height(80.f)}, {200, 48});
    const auto quitBtn  = new ButtonWidget({dim.WidthRight(20.f), dim.Height(80.f)}, {200, 48});

    helloBtn->AddChild(quitBtn);

    return helloBtn;
}

int WINAPI WinMain(_In_ HINSTANCE hInstance,
                   _In_opt_ HINSTANCE hPrevInstance,
                   _In_ LPSTR lpCmdLine,
                   _In_ int nCmdShow) {
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
    g_hInst = hInstance;

    DemoApp demoApp(800, 400, "XenUI Demo");
    demoApp.Run();

    return S_OK;
}
