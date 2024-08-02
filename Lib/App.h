// Author: Jake Rieger
// Created: 8/1/2024.
//

#pragma once

#include "Canvas.h"
#include "Widget.h"
#include "Window.h"

#include <memory>

namespace XenUI {
    class IApp {
    public:
        IApp(int width, int height, const std::string& title);
        void Run();

        virtual ~IApp()            = default;
        virtual IWidget* BuildUI() = 0;

    protected:
        std::unique_ptr<Window> m_Window;
        std::unique_ptr<Canvas> m_Canvas;
    };
}  // namespace XenUI
