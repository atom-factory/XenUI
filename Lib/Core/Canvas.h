// Author: Jake Rieger
// Created: 8/2/2024.
//

#pragma once

#include "Color.h"
#include "Context.h"
#include "Platform.h"
#include "Widget.h"
#include "Window.h"

namespace XenUI {
    class Canvas {
    public:
        Canvas(const Window* window,
               const Shared<EventDispatcher>& dispatcher,
               const Color& backgroundColor);
        ~Canvas();
        void Draw(IWidget* root) const;

        Size<f32> GetSize() const {
            return m_Size;
        }

    private:
        void Resize(int width, int height);

        Size<f32> m_Size;
        Color m_BackgroundColor;

        Shared<EventDispatcher> m_pDispatcher;
        Unique<Context> m_Context;
    };
}  // namespace XenUI
