// Author: Jake Rieger
// Created: 8/2/2024.
//

#pragma once

#include "Platform.h"

namespace XenUI {
    class Canvas {
    public:
        explicit Canvas(HWND window);
        ~Canvas();
        void Draw() const;

    private:
        ComPtr<ID2D1Factory> m_pFactory;
        ComPtr<ID2D1HwndRenderTarget> m_pRenderTarget;
    };
}  // namespace XenUI
