// Author: Jake Rieger
// Created: 8/1/2024.
//

#pragma once

#include "Canvas.h"
#include "Window.h"

#include <memory>

namespace XenUI {
    class IApp {
    public:
        IApp(int width, int height, const std::string& title);
        void Run() const;

    protected:
        std::unique_ptr<Window> m_Window;
        std::unique_ptr<Canvas> m_Canvas;
    };
}  // namespace XenUI
