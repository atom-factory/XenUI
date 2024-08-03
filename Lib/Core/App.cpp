// Author: Jake Rieger
// Created: 8/1/2024.
//

#include "App.h"
#include "Canvas.h"
#include "Events.h"

namespace XenUI {
    IApp::IApp(int width, int height, const std::string& title, const WindowStyle& windowStyle) {
        m_pDispatcher = std::make_shared<EventDispatcher>();

        m_pWindow =
          std::make_unique<Window>(this, m_pDispatcher, nullptr, SW_SHOWNORMAL, width, height);
        m_pWindow->SetTitle(title);
        m_pCanvas =
          std::make_unique<Canvas>(m_pWindow.get(), m_pDispatcher, windowStyle.BackgroundColor);

        m_pDispatcher->RegisterListener<PaintEvent>([this](const PaintEvent& event) { OnPaint(); });
    }

    void IApp::Run() const {
        while (!m_pWindow->ShouldClose()) {
            m_pWindow->DispatchMessages();
        }
    }

    void IApp::OnPaint() {
        m_pCanvas->Draw(BuildUI());
    }
}  // namespace XenUI