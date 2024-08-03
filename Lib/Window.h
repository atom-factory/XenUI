// Author: Jake Rieger
// Created: 8/2/2024.
//

#pragma once

#include "EventSystem.h"
#include "Platform.h"

namespace XenUI {
    class IApp;

    class Window {
    public:
        Window(IApp* owner,
               const std::shared_ptr<EventDispatcher>& dispatcher,
               HINSTANCE hInstance,
               int nCmdShow,
               int width,
               int height,
               LPCSTR className = "XenAppWindowClass",
               LPCSTR title     = "Xen App");
        ~Window();

        /// Setters and control methods
        void SetTitle(const std::string& title);
        void SetSize(int width, int height) const;
        void SetPosition(int x, int y) const;
        void SetIcon(const char* icoFile);
        void SetStyle(LONG style, LONG exStyle) const;
        void Minimize() const;
        void Maximize() const;
        void Restore() const;
        void TriggerRedraw() const;
        void DispatchMessages();

        /// Getters
        [[nodiscard]] HWND GetHandle() const {
            return m_hWnd;
        }

        [[nodiscard]] std::shared_ptr<EventDispatcher> GetDispatcher() const {
            return m_pDispatcher;
        }

        [[nodiscard]] bool ShouldClose() const {
            return m_ShouldClose;
        }

        /// Event handlers
        void OnPaint() const;
        void OnResize(int width, int height) const;

        /// Win32 window process callback
        static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

    private:
        ATOM RegisterWindowClass(HINSTANCE hInstance) const;
        void InitializeInstance(HINSTANCE hInstance, int nCmdShow);

        HWND m_hWnd;
        LPCSTR m_ClassName;
        LPCSTR m_Title;
        int m_Width;
        int m_Height;
        bool m_ShouldClose;
        MSG m_Msg;

        std::shared_ptr<EventDispatcher> m_pDispatcher;
        IApp* m_pOwner;
    };
}  // namespace XenUI
