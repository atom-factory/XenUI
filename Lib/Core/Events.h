// Author: Jake Rieger
// Created: 8/3/2024.
//

#pragma once

#include "EventSystem.h"

namespace XenUI {
    class PaintEvent final : public IEvent {
    public:
        PaintEvent() = default;
    };

    class CloseEvent final : public IEvent {
    public:
        CloseEvent() = default;
    };

    class ResizeEvent final : public IEvent {
    public:
        ResizeEvent(int width, int height) : Width(width), Height(height) {}
        int Width;
        int Height;
    };
}  // namespace XenUI