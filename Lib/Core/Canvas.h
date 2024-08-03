// Author: Jake Rieger
// Created: 8/2/2024.
//

#pragma once

#include "Platform.h"
#include "Widget.h"
#include "Window.h"

namespace XenUI {
    class Canvas {
    public:
        Canvas(const Window* window, const std::shared_ptr<EventDispatcher>& dispatcher);
        ~Canvas();
        void Draw(IWidget* root) const;

    private:
        void Resize(int width, int height);

        Size<f32> m_Size;

        std::shared_ptr<EventDispatcher> m_pDispatcher;
        ComPtr<ID2D1Factory> m_pFactory;
        ComPtr<ID2D1HwndRenderTarget> m_pRenderTarget;
    };
}  // namespace XenUI
