// Author: Jake Rieger
// Created: 8/3/2024.
//

#include "Rectangle.h"

namespace XenUI {
    Rectangle Rectangle::Largest = FromPoints(Offset(0.f, 0.f), Offset(Inf32, Inf32));
    Rectangle Rectangle::Zero    = {0, 0, 0, 0};

    Rectangle::Rectangle(const Offset& offset, const Size<f32>& size) {
        Top    = offset.Y;
        Left   = offset.X;
        Right  = offset.X + size.Width;
        Bottom = offset.Y + size.Height;
    }

    Rectangle::Rectangle(const f32 left, const f32 top, const f32 right, const f32 bottom)
        : Left(left), Top(top), Right(right), Bottom(bottom) {}

    Rectangle Rectangle::FromCenter(const Offset& center, const f32 width, const f32 height) {
        const auto left   = center.X - (width / 2);
        const auto top    = center.Y - (height / 2);
        const auto right  = center.X + (width / 2);
        const auto bottom = center.Y + (height / 2);
        return {left, top, right, bottom};
    }

    Rectangle Rectangle::FromCircle(const Offset& center, const f32 radius) {
        return FromCenter(center, radius * 2, radius * 2);
    }

    Rectangle
    Rectangle::FromLTWH(const f32 left, const f32 top, const f32 width, const f32 height) {
        return {left, top, left + width, top + height};
    }

    Rectangle Rectangle::FromPoints(const Offset& a, const Offset& b) {
        return {std::min(a.X, b.X), std::min(a.Y, b.Y), std::max(a.X, b.X), std::max(a.Y, b.Y)};
    }

    Rectangle Rectangle::Copy(const Rectangle& other) {
        return {other.Left, other.Top, other.Right, other.Bottom};
    }

    f32 Rectangle::Height() const {
        return Bottom - Top;
    }
    f32 Rectangle::Width() const {
        return Right - Left;
    }
    f32 Rectangle::LongestSide() const {
        return std::max(Width(), Height());
    }
    f32 Rectangle::ShortestSide() const {
        return std::min(Width(), Height());
    }

    Offset Rectangle::BottomCenter() const {
        return {Left + Width() / 2.f, Bottom};
    }
    Offset Rectangle::BottomLeft() const {
        return {Left, Bottom};
    }
    Offset Rectangle::BottomRight() const {
        return {Right, Bottom};
    }
    Offset Rectangle::Center() const {
        return {Left + Width() / 2.f, Top + Height() / 2.f};
    }
    Offset Rectangle::CenterLeft() const {
        return {Left, Top + Height() / 2.f};
    }
    Offset Rectangle::CenterRight() const {
        return {Right, Top + Height() / 2.f};
    }
    Offset Rectangle::TopCenter() const {
        return {Left + Width() / 2.f, Top};
    }
    Offset Rectangle::TopLeft() const {
        return {Left, Top};
    }
    Offset Rectangle::TopRight() const {
        return {Right, Top};
    }

    bool Rectangle::Contains(const Offset& offset) const {
        return offset.X >= Left && offset.X < Right && offset.Y >= Top && offset.Y < Bottom;
    }

    bool Rectangle::Overlaps(const Rectangle& other) const {
        if (Right <= other.Left || other.Right <= Left) {
            return false;
        }
        if (Bottom <= other.Top || other.Bottom <= Top) {
            return false;
        }
        return true;
    }

    Rectangle Rectangle::Shrink(const f32 delta) const {
        return {Left + delta, Top + delta, Right - delta, Bottom - delta};
    }

    Rectangle Rectangle::BoundingBox(const Rectangle& other) const {
        return {std::min(Left, other.Left),
                std::min(Top, other.Top),
                std::max(Right, other.Right),
                std::max(Bottom, other.Bottom)};
    }

    Rectangle Rectangle::Grow(const f32 delta) const {
        return {Left - delta, Top - delta, Right + delta, Bottom + delta};
    }

    Rectangle Rectangle::Intersect(const Rectangle& other) const {
        return {std::max(Left, other.Left),
                std::max(Top, other.Top),
                std::min(Right, other.Right),
                std::min(Bottom, other.Bottom)};
    }

    Rectangle Rectangle::Shift(const Offset& offset) const {
        return {Left + offset.X, Top + offset.Y, Right + offset.X, Bottom + offset.Y};
    }

    Rectangle Rectangle::Translate(const f32 translateX, const f32 translateY) const {
        return {Left + translateX, Top + translateY, Right + translateX, Bottom + translateY};
    }

    Rectangle Rectangle::Lerp(const Rectangle& a, const Rectangle& b, const f32 t) {
        return {Math::Lerp(a.Left, b.Left, t),
                Math::Lerp(a.Top, b.Top, t),
                Math::Lerp(a.Right, b.Right, t),
                Math::Lerp(a.Bottom, b.Bottom, t)};
    }
}  // namespace XenUI