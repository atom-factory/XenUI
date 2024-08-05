#include "Core/Platform.h"
#include "Core/App.h"
#include "Core/Window.h"
#include "Core/Dimension.h"
#include "Core/Interactive.h"

#include <memory>

using namespace XenUI;

namespace {
    HINSTANCE g_hInst;
}  // namespace

/// This defines a simple button widget to display on screen.
/// You can define your own widgets like this or use any of the
/// built-in widgets found in `Widgets/`
class CustomButton final : public IWidget,
                           public IInteractive {
public:
    CustomButton(const Offset& position,
                 const Size<f32>& size,
                 const Color& color,
                 const str& text,
                 const std::function<void()>& onPressed)
        : IWidget(position, size), m_Color(color), m_Text(text), m_OnPressed(onPressed) {}
    void Draw(Context* context, const Dimension& dim) override {
        // Draw a cyan-colored rectangle with rounded corners
        const auto stroke = StrokeProperties(2.f, m_Color);
        context->DrawRect(GetRect(), m_Color.WithAlpha(0.1f), stroke, true, 8.f);
        context->DrawString(m_Text, 18.f, m_Position, m_Size, m_Color);
    }

    void OnPressed() override {
        m_OnPressed();
    }

private:
    Color m_Color;
    str m_Text;
    std::function<void()> m_OnPressed;
};

class DemoApp final : public IApp {
public:
    DemoApp(int width, int height, const std::string& title) : XenUI::IApp(width, height, title) {
        m_pWindow->SetIcon("app.ico");
    }

    IWidget* BuildUI(Context* context) override;
};

IWidget* DemoApp::BuildUI(Context* context) {
    const auto dim = m_pCanvas->GetDimension();

    const auto onSayHello = [this]() {
        ::MessageBoxA(m_pWindow->GetHandle(), "Hello!", "XenUI Demo", MB_OK);
    };
    const auto onQuit = [this]() { this->Quit(); };

    const auto sayHelloButton = new CustomButton({dim.Width(50.f), dim.HeightBottom(14.f) - 72.f},
                                                 {dim.Width(90.f), 52.f},
                                                 Color(0xFFFF3636),
                                                 "Say Hello",
                                                 onSayHello);

    const auto quitButton = new CustomButton({dim.Width(50.f), dim.HeightBottom(14.f)},
                                             {dim.Width(90.f), 52.f},
                                             Color(0xFF2ac3de),
                                             "Quit",
                                             onQuit);

    quitButton->AddChild(sayHelloButton);

    return quitButton;
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
