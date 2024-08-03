// Author: Jake Rieger
// Created: 8/3/2024.
//

#include "Context.h"

namespace XenUI {
    Context::Context(HWND hwnd) {
        ThrowIfFailed(
          D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, IID_PPV_ARGS(&m_pFactory)));

        RECT rc;
        ::GetClientRect(hwnd, &rc);
        ThrowIfFailed(m_pFactory->CreateHwndRenderTarget(
          D2D1::RenderTargetProperties(),
          D2D1::HwndRenderTargetProperties(hwnd, D2D1::SizeU(rc.right, rc.bottom)),
          &m_pRenderTarget));
    }

    Context::~Context() {
        if (m_pRenderTarget) {
            m_pRenderTarget.Reset();
        }

        if (m_pFactory) {
            m_pFactory.Reset();
        }
    }

    void Context::Resize(int width, int height) const {
        if (m_pRenderTarget) {
            ThrowIfFailed(m_pRenderTarget->Resize(D2D1_SIZE_U(width, height)));
        }
    }

    ID2D1SolidColorBrush* Context::CreateColorBrush(const Color& color) const {
        ID2D1SolidColorBrush* brush = nullptr;
        ThrowIfFailed(m_pRenderTarget->CreateSolidColorBrush(color.GetD2DColor(), &brush));

        return brush;
    }

    ID2D1LinearGradientBrush* Context::CreateLinearGradientBrush() {
        return nullptr;
    }

    ID2D1RadialGradientBrush* Context::CreateRadialGradientBrush() {
        return nullptr;
    }
}  // namespace XenUI