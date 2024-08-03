// Author: Jake Rieger
// Created: 8/3/2024.
//

#pragma once

#include "Platform.h"

namespace XenUI {
    class Context {
    public:
        Context();
        ~Context();

        [[nodiscard]] ID2D1Factory* GetD2DFactory() const {
            return factory.Get();
        }

        [[nodiscard]] ID2D1HwndRenderTarget* GetD2DRenderTarget() const {
            return renderTarget.Get();
        }

    private:
        ComPtr<ID2D1Factory> factory;
        ComPtr<ID2D1HwndRenderTarget> renderTarget;
    };
}  // namespace XenUI
