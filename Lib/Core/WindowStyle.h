// Author: Jake Rieger
// Created: 8/3/2024.
//

#pragma once
#include "Color.h"

namespace XenUI {
    struct WindowStyle {
        Color BackgroundColor;
        bool Borderless {};
        bool Resizable {};
        bool CanMinimize {};
        bool CanMaximize {};
        bool Titlebar {};

        static WindowStyle Default() {
            return {
              .BackgroundColor = Color(0xFFF1F1F1),
              .Borderless      = false,
              .Resizable       = true,
              .CanMinimize     = true,
              .CanMaximize     = true,
              .Titlebar        = true,
            };
        }
    };
}  // namespace XenUI