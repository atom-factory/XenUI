// Author: Jake Rieger
// Created: 8/5/2024.
//

#pragma once

#include "Color.h"
#include "Types.h"

namespace XenUI {
    enum class StrokeType { Solid, Dashed, Dotted, Double };

    enum class StrokeOrigin { Inside, Center, Outside };

    class StrokeProperties {
    public:
        f32 width           = 0.f;
        Color color         = Colors::Black;
        StrokeType type     = StrokeType::Solid;
        StrokeOrigin origin = StrokeOrigin::Outside;
    };

}  // namespace XenUI
