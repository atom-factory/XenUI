// Author: Jake Rieger
// Created: 8/3/2024.
//

#pragma once

#include "Mathematics.h"
#include "Offset.h"

namespace XenUI {
    using Math::FiniteFloat;

    template<FiniteFloat T = f32>
    class Size {
    public:
        Size(T width, T height);

        static Size Copy(Size& other);
        static Size FromRadius(T radius);
        static Size Square(T dimension);
        static Size FromHeight(T height);
        static Size FromWidth(T width);

        T GetAspectRatio();
        T GetHypotenuse();

        template<FiniteFloat newT>
        Size<newT> To();

        Offset AsOffset();
        void Set(T x, T y);

        T Width;
        T Height;
    };

    template<FiniteFloat T>
    Size<T>::Size(T width, T height) : Width(width), Height(height) {}

    template<FiniteFloat T>
    Size<T> Size<T>::Copy(Size& other) {
        return Size(other.Width, other.Height);
    }

    template<FiniteFloat T>
    Size<T> Size<T>::FromRadius(T radius) {
        return Size(radius * 2, radius * 2);
    }

    template<FiniteFloat T>
    Size<T> Size<T>::Square(T dimension) {
        return Size(dimension, dimension);
    }

    template<FiniteFloat T>
    Size<T> Size<T>::FromHeight(T height) {
        return Size(height, height);
    }

    template<FiniteFloat T>
    Size<T> Size<T>::FromWidth(T width) {
        return Size(width, width);
    }

    template<FiniteFloat T>
    T Size<T>::GetAspectRatio() {
        return Width / Height;
    }

    template<FiniteFloat T>
    T Size<T>::GetHypotenuse() {
        return sqrt(Width * Width + Height * Height);
    }

    template<FiniteFloat T>
    template<FiniteFloat newT>
    Size<newT> Size<T>::To() {
        return Size<newT>(CAST<newT>(Width), CAST<newT>(Height));
    }

    template<FiniteFloat T>
    Offset Size<T>::AsOffset() {
        return Offset(Width, Height);
    }

    template<FiniteFloat T>
    void Size<T>::Set(T x, T y) {
        Width  = x;
        Height = y;
    }
}  // namespace XenUI
