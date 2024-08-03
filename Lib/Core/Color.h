#pragma once

#include "Types.h"
#include "Platform.h"

namespace XenUI {
    class Color {
    public:
        Color();
        Color(f32 r, f32 g, f32 b, f32 a = 1.0);
        explicit Color(u32 color);

        [[nodiscard]] u32 Value() const;
        [[nodiscard]] f32 Luminance() const;
        [[nodiscard]] Color WithAlpha(u32 a) const;
        [[nodiscard]] Color WithAlpha(f32 a) const;
        [[nodiscard]] Color WithRed(u32 r) const;
        [[nodiscard]] Color WithRed(f32 r) const;
        [[nodiscard]] Color WithGreen(u32 g) const;
        [[nodiscard]] Color WithGreen(f32 g) const;
        [[nodiscard]] Color WithBlue(u32 b) const;
        [[nodiscard]] Color WithBlue(f32 b) const;
        [[nodiscard]] Color Greyscale() const;

        static Color AlphaBlend(const Color& foreground, const Color& background);
        static u32 GetAlphaFromOpacity(f32 opacity);
        static Color Lerp(const Color& a, const Color& b, f32 t);
        static f32 LinearizeComponent(f32 c);

        [[nodiscard]] D2D1_COLOR_F GetD2DColor() const;

        f32 Red;
        f32 Green;
        f32 Blue;
        f32 Alpha;
    };

    namespace Colors {
        inline static auto White       = Color(0xFFFFFFFF);
        inline static auto Black       = Color(0xFF000000);
        inline static auto Red         = Color(0xFFFF0000);
        inline static auto Yellow      = Color(0xFFFFFF00);
        inline static auto Green       = Color(0xFF00FF00);
        inline static auto Cyan        = Color(0xFF00FFFF);
        inline static auto Blue        = Color(0xFF0000FF);
        inline static auto Magenta     = Color(0xFFFF00FF);
        inline static auto Transparent = Color(0x00000000);
    }  // namespace Colors

    inline void HexToRGBA(const u32 hex, f32& r, f32& g, f32& b, f32& a) {
        const u8 alphaByte = (hex >> 24) & 0xFF;
        const u8 redByte   = (hex >> 16) & 0xFF;
        const u8 greenByte = (hex >> 8) & 0xFF;
        const u8 blueByte  = hex & 0xFF;

        a = CAST<f32>(CAST<u32>(alphaByte) / 255.0);
        r = CAST<f32>(CAST<u32>(redByte) / 255.0);
        g = CAST<f32>(CAST<u32>(greenByte) / 255.0);
        b = CAST<f32>(CAST<u32>(blueByte) / 255.0);
    }

    inline void HexToRGBA(const u32 hex, u32& r, u32& g, u32& b, u32& a) {
        const u8 alphaByte = (hex >> 24) & 0xFF;
        const u8 redByte   = (hex >> 16) & 0xFF;
        const u8 greenByte = (hex >> 8) & 0xFF;
        const u8 blueByte  = hex & 0xFF;

        a = CAST<u32>(alphaByte);
        r = CAST<u32>(redByte);
        g = CAST<u32>(greenByte);
        b = CAST<u32>(blueByte);
    }

    inline u32 RGBAToHex(const f32 r, const f32 g, const f32 b, const f32 a) {
        const auto redByte   = CAST<u8>(r * 255.0f);
        const auto greenByte = CAST<u8>(g * 255.0f);
        const auto blueByte  = CAST<u8>(b * 255.0f);
        const auto alphaByte = CAST<u8>(a * 255.0f);

        return (alphaByte << 24) | (redByte << 16) | (greenByte << 8) | blueByte;
    }

}  // namespace XenUI