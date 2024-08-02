// Author: Jake Rieger
// Created: 8/2/2024.
//

#pragma once

#include "Platform.h"

#include <atomic>

namespace XenUI {
    class Window {
    public:
        Window(HINSTANCE hInstance,
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
        void Show();
        void TriggerRedraw() const;

        /// Event handlers
        void OnPaint();
        void OnResize(int width, int height);

        /// Win32 window process callback
        static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

    private:
        ATOM RegisterWindowClass(HINSTANCE hInstance) const;
        void InitializeInstance(HINSTANCE hInstance, int nCmdShow);
        static void EventLoop();

        HWND m_hWnd;
        LPCSTR m_ClassName;
        LPCSTR m_Title;
        std::atomic<bool> m_isRunning;
        int m_Width;
        int m_Height;
    };
}  // namespace XenUI
