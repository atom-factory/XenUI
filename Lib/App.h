// Author: Jake Rieger
// Created: 8/1/2024.
//

#pragma once

#include "EventSystem.h"
#include "Widget.h"
#include "Window.h"
#include "Canvas.h"

#include <memory>

namespace XenUI {
    class IApp {
    public:
        IApp(int width, int height, const std::string& title);
        void Run() const;

        virtual ~IApp()            = default;
        virtual IWidget* BuildUI() = 0;

    protected:
        void OnPaint();

        std::unique_ptr<Window> m_pWindow;
        std::unique_ptr<Canvas> m_pCanvas;
        std::shared_ptr<EventDispatcher> m_pDispatcher;
    };
}  // namespace XenUI
