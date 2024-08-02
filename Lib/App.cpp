// Author: Jake Rieger
// Created: 8/1/2024.
//

#include "App.h"

namespace XenUI {
    IApp::IApp(int width, int height, const std::string& title) {
        m_Window = std::make_unique<Window>(nullptr, SW_SHOW, width, height);
        m_Window->SetTitle(title);

        m_Canvas = std::make_unique<Canvas>(m_Window->GetHandle());
    }

    void IApp::Run() const {
        while (!m_Window->ShouldClose()) {
            m_Window->DispatchMessages();
            m_Canvas->Draw();
        }
    }
}  // namespace XenUI