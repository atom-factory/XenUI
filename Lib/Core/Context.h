// Author: Jake Rieger
// Created: 8/3/2024.
//

#pragma once

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

        ID2D1SolidColorBrush* CreateColorBrush();
        ID2D1LinearGradientBrush* CreateLinearGradientBrush();
        ID2D1RadialGradientBrush* CreateRadialGradientBrush();

    private:
        ComPtr<ID2D1Factory> m_pFactory;
        ComPtr<ID2D1HwndRenderTarget> m_pRenderTarget;
    };
}  // namespace XenUI
