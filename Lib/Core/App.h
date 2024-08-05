// Author: Jake Rieger
// Created: 8/1/2024.
//

#pragma once

#include "EventSystem.h"
#include "Widget.h"
#include "Window.h"
#include "Canvas.h"
#include "Events.h"
#include "WindowStyle.h"

#include <memory>

namespace XenUI {
    /// This is the crux of a XenUI application, and the only required component.
    class IApp {
    public:
        IApp(int width,
             int height,
             const std::string& title,
             const WindowStyle& windowStyle = WindowStyle::DefaultDark());
        void Run() const;

        virtual ~IApp() = default;

        /// @brief This is where we define our UI. The UI is a tree of widgets and
        /// `BuildUI()` returns the root widget.
        ///
        /// The tree is built by calling `AddChild` on the parent and passing the
        /// child widget to it. Any widget can have any number of children and the
        /// tree is traversed breadth-first (see Canvas::Draw()).
        ///
        ///  @note Complex UIs will likely be broken up in to separate build methods
        ///  that are called from `BuildUI`.
        virtual IWidget* BuildUI(Context* context) = 0;

        void OnMouseButton(const MouseButtonEvent& event) const;
        void OnMouseMove(const MouseMoveEvent& event) const;

        /// @brief Safely terminates the app. This is the only method that should be used to do so.
        void Quit() const {
            m_pWindow->SetShouldClose(true);
        }

    protected:
        void OnPaint();

        Unique<Window> m_pWindow;
        Unique<Canvas> m_pCanvas;
        Shared<EventDispatcher> m_pDispatcher;
        IWidget* m_pCurrentTree;
    };
}  // namespace XenUI
