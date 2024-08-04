// Author: Jake Rieger
// Created: 8/3/2024.
//

#pragma once

#include "Color.h"
#include "Platform.h"

namespace XenUI {
    class Context {
    public:
        explicit Context(HWND hwnd);
        ~Context();

        void Resize(int width, int height) const;

        [[nodiscard]] ID2D1Factory* GetD2DFactory() const {
            return m_pFactory.Get();
        }

        [[nodiscard]] ID2D1HwndRenderTarget* GetD2DRenderTarget() const {
            return m_pRenderTarget.Get();
        }

        /// @brief Tells Direct2D to re-render the canvas. This will cause a complete frame
        /// redraw and doesn't trigger widget tree rebuilds (see IApp::OnPaint()).
        void TriggerRebuild() const {
            ::InvalidateRect(m_Hwnd, nullptr, false);
        }

    private:
        ComPtr<ID2D1Factory> m_pFactory;
        ComPtr<ID2D1HwndRenderTarget> m_pRenderTarget;
        HWND m_Hwnd;
    };
}  // namespace XenUI
