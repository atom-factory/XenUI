// Author: Jake Rieger
// Created: 8/3/2024.
//

// Yes, "Mathematics" is an overly verbose filename, but Math.h is a system header
// and MSVC freaks out if I call it that.

#pragma once

#include <concepts>
#include <cmath>

namespace XenUI::Math {
    template<typename T>
    concept FiniteFloat = std::floating_point<T> && requires(T value) {
        { std::isfinite(value) } -> std::convertible_to<bool>;
    };

    template<FiniteFloat T>
    T Lerp(T a, T b, double t) {
        if (a == b) {
            return a;
        }

        auto result = a * (1.0 - t) + b * t;
        return CAST<T>(result);
    }
}  // namespace XenUI::Math