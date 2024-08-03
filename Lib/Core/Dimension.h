// Author: Jake Rieger
// Created: 8/3/2024.
//

#pragma once

#include "Types.h"
#include "Size.h"

namespace XenUI {
    class Dimension {
    public:
        explicit Dimension(const Size<f32>& viewSize) : m_Size(viewSize) {}

        [[nodiscard]] f32 Width(const f32 value) const {
            return (value / 100.f) * m_Size.Width;
        }

        [[nodiscard]] f32 Height(const f32 value) const {
            return (value / 100.f) * m_Size.Height;
        }

        [[nodiscard]] f32 WidthRight(const f32 value) const {
            const auto width = Width(value);
            return m_Size.Width - width;
        }

        [[nodiscard]] f32 HeightBottom(const f32 value) const {
            const auto height = Height(value);
            return m_Size.Height - height;
        }

    private:
        Size<f32> m_Size;
    };
}  // namespace XenUI